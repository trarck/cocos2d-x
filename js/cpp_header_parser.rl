=begin
cpp_header_parser.rl
(c) Rolando Abarca, 2011

very simple c++ header parser, used mainly for generating bindings for JavaScriptCore
=end

require 'rubygems'
require 'ruby-debug'

class String
  def zcapitalize
    self[0].upcase + self[1,length-1]
  end
end

%%{
  # % - fix syntax highlight

	machine cpp_header_parser;
	white = [\t ];
	visibility_token = ('public' | 'private' | 'protected') white* ':';
  c_comment := 
    any* :>> '*/'
    @{ fgoto main; };

  main := |*
    'class'          { parser.found_token(:class, p) };
    'enum'           { parser.found_token(:enum, p) };
    'static'         { parser.found_token(:static, p) };
    visibility_token { parser.found_token(:public, p) };
    '*'              { parser.found_token(:star, p) };
    ':'              { parser.found_token(:colon, p) };
    ','              { parser.found_token(:comma, p) };
    ';'              { parser.found_token(:semicolon, p) };
    '{'              { parser.found_token(:open_bracket, p) };
    '}'              { parser.found_token(:close_bracket, p) };
    '};'             { parser.found_token(:close_class, p) };
    '('              { parser.found_token(:open_parenthesis, p) };
    ')'              { parser.found_token(:close_parenthesis, p) };
    '&'              { parser.found_token(:ampersand, p) };
    '='              { parser.found_token(:equals, p) };
    '::'             { parser.found_token(:ns_sep, p) };

    # values
    ([0-9]+) > { parser.token_begin(:number, p) } { parser.found_token(:number, p) };
    ([a-zA-Z_] [a-zA-Z0-9_]*) > { parser.token_begin(:id, p) } { parser.found_token(:id, p) };

  	# Comments and whitespace
  	'/*' { fgoto c_comment; };
  	'//' [^\n]* '\n';
  	( any - 33..126 )+;
  *|;

}%%
# % - fix fynxtax highlight

%% write data;
# % fix syntax highlight

class CppEnum
  @@enum_series = 0

  def initialize(parser)
    @parser = parser
    @last_value = 0
    @waiting_for = nil
    @name = nil
    @keys = []
  end

  # the enums should be global, and if they have a name, then a
  # "namespace" is created, e.g.:
  #
  # typedef enum {
  #   ValOne,
  #   ValTwo,
  #   ValThree
  # } someEnum;
  #
  # will be translated to the following in js:
  #
  # someEnum = {};
  # someEnum.ValOne = 0;
  # someEnum.ValTwo = 1;
  # someEnum.ValThree = 2;
  #
  # The above generated using the JavaScriptCore API
  def generate_binding_code
    str = ""
    object = "GLOBAL_OBJECT"
    if @name
      object = "__js__#{@name}"
      str << "static JSObjectRef #{object} = JSObjectMake(GLOBAL_CTX, NULL, NULL);\n";
    end
    str << "void registerEnum#{@enum_id}()\n{\n"
    str << "\tJSStringRef __tmp;\n"
    @keys.each do |key|
      str << "\t__tmp = JSStringCreateWithUTF8CString(\"#{key[:name]}\");\n"
      str << "\tJSObjectSetProperty(GLOBAL_CTX, #{object}, __tmp, JSValueMakeNumber(GLOBAL_CTX, #{key[:value]}), kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete, NULL);\n"
      str << "\tJSStringRelease(__tmp);\n"
    end
    if @name
      str << "\t__tmp = JSStringCreateWithUTF8CString(\"#{@name}\");\n"
      str << "\tJSObjectSetProperty(GLOBAL_CTX, GLOBAL_OBJ, __tmp, #{object}, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete, NULL);\n"
      str << "\tJSStringRelease(__tmp);\n"
    end
    str << "}\n\n"
    str
  end

  def generate_header_code
    "void registerEnum#{@enum_id}();\n"
  end

  def process_token(token, token_type)
    # puts "got token #{token_type}"
    case token_type
    when :id
      if @waiting_for == :id
        @keys << {:name => token, :value => @last_value}
        @last_value += 1
      elsif @waiting_for == :value
        @keys[-1][:value] = token
        @waiting_for = :id
      elsif @waiting_for == :enum_name
        @name = token
        @waiting_for = :semicolon
      else
        raise "parser error (invalid token in enum: #{token_type})"
      end
    when :equals
      @waiting_for = :value
    when :number
      val = token.to_i
      @keys[-1][:value] = val
      @last_value  = val + 1
    when :open_bracket, :comma
      @waiting_for = :id
    when :close_bracket
      @waiting_for = :enum_name
    when :semicolon
      raise "parser error (invalid token in enum)" unless @waiting_for == :semicolon
      @enum_id = @@enum_series
      @@enum_series += 1
      @parser.enum_ended(self)
    else
      raise "parser error (invalid token in enum: #{token_type})"
    end
  end

  def to_s
    {:name => @name, :keys => @keys}.inspect
  end
end

class CppMethod
  NATIVE_TYPES = %w(int long char float bool short CGFloat)
  FLOAT_TYPES = %w(float double)
  INT_TYPES = %w(int short)
  NUMBER_TYPES = %w(int long float long\ long unsigned\ int signed\ int short CGFloat)
  attr_reader :static, :name, :arguments, :type, :return_type
  attr_accessor :min_arg_count

  def initialize(parser, static = false)
    @parser = parser
    @waiting_for = :return_type
    @static = static
    @name = nil
    @return_type = []
    @arguments = []
    @min_arg_count = 1000 # arbitrary big number
    @current_argument = []
    @type = :invalid
  end

  # this generates a static method that returns a JSValueRef
  # encapsulating the original method. The method then needs to be
  # registered for the class
  def generate_binding_code(klass, indent_level = 1, content_only = false)
    indent = "\t" * indent_level
    str = ""
    str << "#{indent}static JSBool js#{@name}(JSContext *cx, uint32_t argc, jsval *vp)\n{\n" unless content_only
    # need to cast arguments from JS to native
    if @arguments.size == @min_arg_count
      str << "#{indent}\tif (argc == #{@arguments.size}) {\n"
      indent += "\t"
    elsif @min_arg_count > 0
      str << "#{indent}\tif (argc >= #{@min_arg_count}) {\n"
      indent += "\t"
    end
    unless @static || @name == klass.name || content_only
      str << "#{indent}\t#{klass.name}* cobj = (#{klass.name} *)JS_GetPrivate(obj);\n"
    end

    # the idea is to create the format string with the required arguments and then
    # the optional arguments. Something like:
    # format_str = "o/ii"
    # for addChild(node, tag, zOrder)
    # where node is required, but tag and zOrder are optional
    format_str = ""
    @arguments.each_with_index do |arg, i|
      if i == @min_arg_count && @arguments.size != @min_arg_count
        format_str << "/"
      end
      if FLOAT_TYPES.include?(arg[:type])
        format_str << "d"
        str << "#{indent}\tdouble arg#{i} = 0.0f;\n"
      elsif INT_TYPES.include?(arg[:type])
        format_str << "i"
        str << "#{indent}\t#{arg[:type]} arg#{i} = 0;\n"
      else
        # it's a pointer or something else, so assume JSObject
        format_str << "o"
        str << "#{indent}\tJSObject *jsarg#{i} = NULL;\n"
        str << "#{indent}\t#{arg[:type]} arg#{i} = (#{arg[:type]})JS_GetPrivate(jsarg#{i});\n"
      end
    end
    # convert the arguments
    if @arguments.size > 0
      arg_list_ptrs = (0...@arguments.size).map { |i| "&arg#{i}" }.join(", ")
      arg_list      = (0...@arguments.size).map { |i| "arg#{i}" }.join(", ")
      str << "#{indent}\tif (JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), \"#{format_str}\", #{arg_list_ptrs}) == JS_TRUE) {\n"
      # do the call
      str << "#{indent}\t\tthis->#{@name}(#{arg_list});\n"
      str << "#{indent}\t\treturn true;\n"
      str << "#{indent}\t}\n"
      str << "#{indent}\treturn false;\n"
    else
      str << "#{indent}\t// do the call here\n"
      str << "#{indent}\treturn true;\n"
    end
    str << "#{indent}};\n" unless content_only
    str
  end

  def append_current_argument
    len = @current_argument.size
    raise "invalid argument" if len < 2
    @arguments << {:type => @current_argument[0, len-1].join(" "), :name => @current_argument[-1]}
    @current_argument = []
  end

  def process_token(token, token_type)
    case token_type
    when :id, :star, :ns_sep
      case @waiting_for
      when :return_type
        case token_type
        when :id
          last_type = @return_type[-1]
          if last_type && last_type[-1] == ":"
            @return_type[-1] = last_type + token
          else
            @return_type << token
          end
        else
          @return_type[-1] = @return_type[-1] + (token_type == :star ? '*' : '::')
        end
      when :argument
        case token_type
        when :id
          last_type = @current_argument[-1]
          if last_type && last_type[-1] == ":"
            @current_argument[-1] = last_type + token
          else
            @current_argument << token
          end
        else
          @current_argument[-1] = @current_argument[-1] + (token_type == :star ? '*' : '::')
        end
      else
        raise "invalid token: #{token}"
      end
    when :open_parenthesis
      @name = @return_type[-1]
      @return_type = @return_type[0, @return_type.length - 1].join(" ")
      @waiting_for = :argument
      @type = :function
    when :comma
      append_current_argument
      @waiting_for = :argument
    when :close_parenthesis
      append_current_argument if @current_argument.size > 0
      @waiting_for = :semicolon
    when :semicolon
      if @type == :invalid
        @name = @return_type[-1]
        @return_type = @return_type[0, @return_type.length - 1].join(" ")
        @type = :attribute
      end
      @parser.method_ended(self)
    end
  end
  
  def to_s
    "{:name => #{@name.inspect}, :static => #{@static}, :return => #{@return_type.inspect}, :arguments => #{@arguments.inspect}}"
  end
end

class CppClass
  attr_reader :public_methods, :name
  attr_accessor :constructor, :begin

  def initialize(name)
    @name = name
    @begin = false
    @constructor = nil
    @public_methods = []
    @all_static = false
  end

  def js_name
    return "S_#{@name}"
  end
  
  def check_all_static
    @all_static = true
    @public_methods.each { |m| @all_static = false unless m.static }
    @all_static
  end

  def generate_binding_code
    check_all_static
    str = ""
    str << 
    str << <<-EOS
class #{js_name} : public #{@name}
{
\tJSObject *m_obj;
\tstatic JSClass*  jsClassDef;
\tstatic JSObject* jsClassObj;
public:
#{generate_properties_enum}

\tbool initWithContext(JSContext *cx, JSObject *obj, uint32_t argc, jsval *vp)
\t{
#{generate_constructor_code}
\t};
\tstatic JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
\t{
#{generate_getter_code}
\t\treturn JS_FALSE;
\t};

\tstatic JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
\t{
#{generate_setter_code}
\t};

\tstatic void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
\t{
\t\tjsClassDef = (JSClass *)calloc(1, sizeof(JSClass));
\t\tjsClassDef->name = name;
\t\tjsClassDef->addProperty = JS_PropertyStub;
\t\tjsClassDef->delProperty = JS_PropertyStub;
\t\tjsClassDef->getProperty = JS_PropertyStub;
\t\tjsClassDef->setProperty = JS_StrictPropertyStub;
\t\tjsClassDef->enumerate = JS_EnumerateStub;
\t\tjsClassDef->resolve = JS_ResolveStub;
\t\tjsClassDef->convert = JS_ConvertStub;
\t\tjsClassDef->finalize = jsFinalize;
\t\tjsClassDef->flags = JSCLASS_HAS_PRIVATE;

#{generate_properties_array}

\t\tjsClassObj = JS_InitClass(cx,globalObj,NULL,jsClassDef,#{js_name}::jsConstructor,0,properties,NULL,NULL,NULL);
\t};

\tstatic void jsFinalize(JSContext *cx, JSObject *obj)
\t{
\t\tCCLog("js finalize object: %p", obj);
\t};

\tstatic JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
\t{
\t\tJSObject *obj = JS_NewObject(cx, #{js_name}::jsClassDef, #{js_name}::jsClassObj, NULL);
\t\t#{js_name} *cobj = new #{js_name}();
\t\tif (cobj->initWithContext(cx, obj, argc, vp)) {
\t\t\tJS_SetPrivate(obj, cobj);
\t\t\tJS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
\t\t\treturn JS_TRUE;
\t\t}
\t\tdelete cobj;
\t\treturn JS_FALSE;
\t};

    EOS
    @public_methods.each do |m|
      m.generate_binding_code if m.type == :function && !m.static
    end
    str << <<-EOS
};
JSClass*  #{js_name}::jsClassDef = NULL;
JSObject* #{js_name}::jsClassObj = NULL;

    EOS
    str
  end

  def public_attributes
    @public_methods.select { |m| m.type == :attribute }
  end

  def generate_getter_code
    attrs = public_attributes
    return "" if attrs.empty?

    str = ""
    str << <<-EOS
\t\tint32_t propId = JSID_TO_INT(_id);
\t\t#{js_name} *cobj = (#{js_name} *)JS_GetPrivate(obj);
\t\tif (!cobj) return JS_FALSE;

\t\tswitch(propId) {
    EOS

    attrs.each do |m|
      str << "\t\tcase k#{m.name.zcapitalize}:\n"
      if CppMethod::INT_TYPES.include?(m.return_type) || CppMethod::FLOAT_TYPES.include?(m.return_type)
        str << "\t\t\tJS_NewNumberValue(cx, cobj->#{m.name}, val);\n"
      end
      str << "\t\t\treturn JS_TRUE;\n"
      str << "\t\t\tbreak;\n"
    end
    str << "\t\tdefault:\n"
    str << "\t\t\tbreak;\n"
    str << "\t\t}\n"
    str
  end

  def generate_setter_code
    attrs = public_attributes
    return "return JS_FALSE;" if attrs.empty?

    str = ""
    str << <<-EOS
\t\tint32_t propId = JSID_TO_INT(_id);
\t\t#{js_name} *cobj = (#{js_name} *)JS_GetPrivate(obj);
\t\tif (!cobj) return JS_FALSE;

\t\tdouble tmpDbl;
\t\tJSBool ret = JS_FALSE;
\t\tswitch(propId) {
    EOS

    attrs.each do |m|
      str << "\t\tcase k#{m.name.zcapitalize}:\n"
      if CppMethod::INT_TYPES.include?(m.return_type) || CppMethod::FLOAT_TYPES.include?(m.return_type)
        str << "\t\t\tJS_ValueToNumber(cx, *val, &tmpDbl);\n"
        str << "\t\t\tcobj->#{m.name} = tmpDbl;\n"
      end
      str << "\t\t\tret = JS_TRUE;\n"
      str << "\t\t\tbreak;\n"
    end

    str << "\t\tdefault:\n"
    str << "\t\t\tbreak;\n"
    str << "\t\t}\n"
    str << "\t\treturn ret;\n"
    str
  end

  def generate_properties_enum
    attrs = public_attributes
    return "" if attrs.empty?

    str = "\tenum {\n"
    array = []
    attrs.each_with_index do |m, i|
      array << "\t\tk#{m.name.zcapitalize}" + (i == 0 ? " = 1" : "")
    end
    str << array.join(",\n") << "\n"
    str << "\t};\n"
  end

  def generate_properties_array
    attrs = public_attributes
    return "" if attrs.empty?

    str = "\t\tstatic JSPropertySpec properties[] = {\n"
    array = []
    attrs.each do |m|
      array << "\t\t\t{\"#{m.name}\", k#{m.name.zcapitalize}, JSPROP_PERMANENT | JSPROP_SHARED, #{js_name}::jsPropertyGet, #{js_name}::jsPropertySet}"
    end
    str << array.join(",\n") << "\n"
    str << "\t\t};\n"
    str
  end

  def generate_constructor_code
    if @constructor
      # output just the body for the constructor
      @constructor.generate_binding_code(self, 1, true)
    end
  end
end

class CppHeaderParser
  attr_accessor :data

  def initialize(data)
    @last_token_position = nil
    @last_token = nil
    @current_class = nil
    @current_method = nil
    @current_enum = nil
    @in_public = false
    @enums = []
    @classes = []
    @data = data
  end

  def token_begin(token, pos)
    if token == :id
      @last_token_begin = pos
    elsif token == :number
      @last_number_begin = pos
    end
  end

  def method_ended(method)
    if @current_method.name =~ /^init/ || @current_method.name == @current_class.name
      if @current_class.constructor
        @current_method.min_arg_count = [@current_method.arguments.size, @current_class.constructor.min_arg_count].min
        # puts "found method: #{@current_method} - #{@current_method.arguments.size},#{@current_class.constructor.min_arg_count},#{@current_method.min_arg_count}"
      else
        @current_method.min_arg_count = @current_method.arguments.size
      end
      @current_class.constructor = @current_method
    else
      @current_class.public_methods << @current_method
    end
    @current_method = nil
  end

  def enum_ended(enum)
    # puts "found enum: #{enum}"
    @enums << @current_enum
    @current_enum = nil
  end

  def found_token(token, pos)
    # puts "found token: #{token}"
    case token
    when :id
      process_id(pos)
    when :number
      raise "parser error" if !@current_enum
      token_val = @data[@last_number_begin, pos - @last_number_begin + 1]
      @current_enum.process_token(token_val, :number)
    when :static
      raise "parsing error" if @current_method
      @current_method = CppMethod.new(self, true) if @in_public
    when :enum
      raise "parsing error" if @current_enum || @current_class
      @current_enum = CppEnum.new(self)
    when :close_class
      # puts @current_class.inspect
      @classes << @current_class
      @current_class = nil
    when :open_bracket
      if @current_class and !@current_class.begin
        @current_class.begin = true
      else
        @current_method.process_token(token.to_s, token) if @current_method
        @current_enum.process_token(token.to_s, token) if @current_enum
      end
    when :public
      if @current_class and @current_class.begin
        @in_public = true
      end
    when :private, :protected
      if @current_class and @current_class.begin
        @in_public = false
      end
    else
      @current_method.process_token(token.to_s, token) if @current_method
      @current_enum.process_token(token.to_s, token) if @current_enum
    end
    @last_token = token
  end

  def generate_binding_code(header_file)
    outname = File.basename(header_file, ".h")
    out = File.open("#{outname}_generated.cpp", "w+")
    # output constants used across code
    out.puts "#include \"cocos2d.h\""
    out.puts "#include \"ScriptingCore.h\"\n\n"
    out.puts "using namespace cocos2d;\n\n"

    # first, output the enums
    @enums.each do |enum|
      out.puts enum.generate_binding_code
    end

    out.puts "\n"

    # now the classes
    @classes.each do |klass|
      out.puts klass.generate_binding_code
    end
    out.close
  end

  def process_id(pos)
    token_val = @data[@last_token_begin, pos - @last_token_begin + 1]
    case @last_token
    when :class
      @current_class = CppClass.new(token_val)
    else
      if @current_class && @in_public
        if @current_method.nil?
          @current_method = CppMethod.new(self)
        end
        @current_method.process_token(token_val, :id)
      elsif @current_enum
        @current_enum.process_token(token_val, :id)
      end
    end
  end
end

def run_machine(parser, fname)
  data = parser.data
  eof = data.length
  line_no = 1

  begin
    %% write init;
    %% write exec;
  rescue => err
    puts "Parser error at line #{line_no}"
    puts err
  end

  if (cs != cpp_header_parser_error)
    parser.generate_binding_code(fname)
  else
    $stderr.puts "error parsing at line #{line_no}"
    $stderr.puts ">> p: #{p} pe: #{pe}; p[p-10,10]: '#{data[p-10,10]}'"
    exit(1)
  end
end

while fname = ARGV.shift
  parser = CppHeaderParser.new(File.read(fname))
  run_machine(parser, File.basename(fname))
end
