
# line 1 "cpp_header_parser.rl"
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


# line 55 "cpp_header_parser.rl"

# % - fix fynxtax highlight


# line 26 "cpp_header_parser.rb"
class << self
	attr_accessor :_cpp_header_parser_actions
	private :_cpp_header_parser_actions, :_cpp_header_parser_actions=
end
self._cpp_header_parser_actions = [
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 10, 1, 
	11, 1, 12, 1, 13, 1, 14, 1, 
	15, 1, 16, 1, 17, 1, 18, 1, 
	19, 1, 20, 1, 21, 1, 22, 1, 
	23, 1, 24, 1, 25, 1, 26, 1, 
	27, 1, 28, 1, 29, 2, 5, 6, 
	2, 5, 7, 2, 5, 8, 2, 5, 
	9, 3, 5, 2, 9
]

class << self
	attr_accessor :_cpp_header_parser_key_offsets
	private :_cpp_header_parser_key_offsets, :_cpp_header_parser_key_offsets=
end
self._cpp_header_parser_key_offsets = [
	0, 0, 2, 3, 6, 7, 9, 39, 
	41, 43, 44, 51, 59, 67, 75, 83, 
	91, 99, 107, 116, 125, 133, 141, 149, 
	157, 167, 175, 183, 191, 199, 207, 215, 
	223, 231, 239, 247, 255, 263, 271, 279, 
	287, 288
]

class << self
	attr_accessor :_cpp_header_parser_trans_keys
	private :_cpp_header_parser_trans_keys, :_cpp_header_parser_trans_keys=
end
self._cpp_header_parser_trans_keys = [
	42, 47, 10, 9, 32, 58, 42, 42, 
	47, 38, 40, 41, 42, 44, 47, 58, 
	59, 61, 95, 99, 101, 112, 115, 123, 
	125, 33, 46, 48, 57, 60, 64, 65, 
	90, 91, 96, 97, 122, 124, 126, 33, 
	126, 48, 57, 58, 95, 48, 57, 65, 
	90, 97, 122, 95, 108, 48, 57, 65, 
	90, 97, 122, 95, 97, 48, 57, 65, 
	90, 98, 122, 95, 115, 48, 57, 65, 
	90, 97, 122, 95, 115, 48, 57, 65, 
	90, 97, 122, 95, 110, 48, 57, 65, 
	90, 97, 122, 95, 117, 48, 57, 65, 
	90, 97, 122, 95, 109, 48, 57, 65, 
	90, 97, 122, 95, 114, 117, 48, 57, 
	65, 90, 97, 122, 95, 105, 111, 48, 
	57, 65, 90, 97, 122, 95, 118, 48, 
	57, 65, 90, 97, 122, 95, 97, 48, 
	57, 65, 90, 98, 122, 95, 116, 48, 
	57, 65, 90, 97, 122, 95, 101, 48, 
	57, 65, 90, 97, 122, 9, 32, 58, 
	95, 48, 57, 65, 90, 97, 122, 95, 
	116, 48, 57, 65, 90, 97, 122, 95, 
	101, 48, 57, 65, 90, 97, 122, 95, 
	99, 48, 57, 65, 90, 97, 122, 95, 
	116, 48, 57, 65, 90, 97, 122, 95, 
	101, 48, 57, 65, 90, 97, 122, 95, 
	100, 48, 57, 65, 90, 97, 122, 95, 
	98, 48, 57, 65, 90, 97, 122, 95, 
	108, 48, 57, 65, 90, 97, 122, 95, 
	105, 48, 57, 65, 90, 97, 122, 95, 
	99, 48, 57, 65, 90, 97, 122, 95, 
	116, 48, 57, 65, 90, 97, 122, 95, 
	97, 48, 57, 65, 90, 98, 122, 95, 
	116, 48, 57, 65, 90, 97, 122, 95, 
	105, 48, 57, 65, 90, 97, 122, 95, 
	99, 48, 57, 65, 90, 97, 122, 59, 
	0
]

class << self
	attr_accessor :_cpp_header_parser_single_lengths
	private :_cpp_header_parser_single_lengths, :_cpp_header_parser_single_lengths=
end
self._cpp_header_parser_single_lengths = [
	0, 2, 1, 3, 1, 2, 16, 0, 
	0, 1, 1, 2, 2, 2, 2, 2, 
	2, 2, 3, 3, 2, 2, 2, 2, 
	4, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	1, 0
]

class << self
	attr_accessor :_cpp_header_parser_range_lengths
	private :_cpp_header_parser_range_lengths, :_cpp_header_parser_range_lengths=
end
self._cpp_header_parser_range_lengths = [
	0, 0, 0, 0, 0, 0, 7, 1, 
	1, 0, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	0, 0
]

class << self
	attr_accessor :_cpp_header_parser_index_offsets
	private :_cpp_header_parser_index_offsets, :_cpp_header_parser_index_offsets=
end
self._cpp_header_parser_index_offsets = [
	0, 0, 3, 5, 9, 11, 14, 38, 
	40, 42, 44, 49, 55, 61, 67, 73, 
	79, 85, 91, 98, 105, 111, 117, 123, 
	129, 137, 143, 149, 155, 161, 167, 173, 
	179, 185, 191, 197, 203, 209, 215, 221, 
	227, 229
]

class << self
	attr_accessor :_cpp_header_parser_indicies
	private :_cpp_header_parser_indicies, :_cpp_header_parser_indicies=
end
self._cpp_header_parser_indicies = [
	0, 2, 1, 3, 2, 5, 5, 6, 
	4, 8, 7, 8, 9, 7, 11, 12, 
	13, 14, 15, 16, 18, 19, 20, 21, 
	22, 23, 24, 25, 26, 27, 1, 17, 
	1, 21, 1, 21, 1, 10, 28, 10, 
	30, 29, 32, 31, 34, 34, 34, 34, 
	33, 34, 36, 34, 34, 34, 35, 34, 
	37, 34, 34, 34, 35, 34, 38, 34, 
	34, 34, 35, 34, 39, 34, 34, 34, 
	35, 34, 40, 34, 34, 34, 35, 34, 
	41, 34, 34, 34, 35, 34, 42, 34, 
	34, 34, 35, 34, 43, 44, 34, 34, 
	34, 35, 34, 45, 46, 34, 34, 34, 
	35, 34, 47, 34, 34, 34, 35, 34, 
	48, 34, 34, 34, 35, 34, 49, 34, 
	34, 34, 35, 34, 50, 34, 34, 34, 
	35, 5, 5, 6, 34, 34, 34, 34, 
	35, 34, 51, 34, 34, 34, 35, 34, 
	52, 34, 34, 34, 35, 34, 53, 34, 
	34, 34, 35, 34, 54, 34, 34, 34, 
	35, 34, 55, 34, 34, 34, 35, 34, 
	50, 34, 34, 34, 35, 34, 56, 34, 
	34, 34, 35, 34, 57, 34, 34, 34, 
	35, 34, 58, 34, 34, 34, 35, 34, 
	50, 34, 34, 34, 35, 34, 59, 34, 
	34, 34, 35, 34, 60, 34, 34, 34, 
	35, 34, 61, 34, 34, 34, 35, 34, 
	62, 34, 34, 34, 35, 34, 63, 34, 
	34, 34, 35, 65, 64, 1, 0
]

class << self
	attr_accessor :_cpp_header_parser_trans_targs
	private :_cpp_header_parser_trans_targs, :_cpp_header_parser_trans_targs=
end
self._cpp_header_parser_trans_targs = [
	6, 0, 2, 6, 6, 3, 6, 4, 
	5, 41, 7, 6, 6, 6, 6, 6, 
	1, 8, 9, 6, 6, 10, 11, 15, 
	18, 35, 6, 40, 6, 6, 8, 6, 
	6, 6, 10, 6, 12, 13, 14, 10, 
	16, 17, 10, 19, 31, 20, 25, 21, 
	22, 23, 24, 26, 27, 28, 29, 30, 
	32, 33, 34, 36, 37, 38, 39, 10, 
	6, 6
]

class << self
	attr_accessor :_cpp_header_parser_trans_actions
	private :_cpp_header_parser_trans_actions, :_cpp_header_parser_trans_actions=
end
self._cpp_header_parser_trans_actions = [
	35, 0, 0, 37, 49, 0, 13, 0, 
	0, 1, 0, 29, 25, 27, 15, 17, 
	0, 3, 0, 19, 31, 65, 5, 5, 
	5, 5, 21, 0, 47, 43, 0, 39, 
	33, 51, 62, 45, 0, 0, 0, 53, 
	0, 0, 56, 0, 0, 0, 0, 0, 
	0, 0, 11, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 59, 
	41, 23
]

class << self
	attr_accessor :_cpp_header_parser_to_state_actions
	private :_cpp_header_parser_to_state_actions, :_cpp_header_parser_to_state_actions=
end
self._cpp_header_parser_to_state_actions = [
	0, 0, 0, 0, 7, 0, 7, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0
]

class << self
	attr_accessor :_cpp_header_parser_from_state_actions
	private :_cpp_header_parser_from_state_actions, :_cpp_header_parser_from_state_actions=
end
self._cpp_header_parser_from_state_actions = [
	0, 0, 0, 0, 0, 0, 9, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0
]

class << self
	attr_accessor :_cpp_header_parser_eof_trans
	private :_cpp_header_parser_eof_trans, :_cpp_header_parser_eof_trans=
end
self._cpp_header_parser_eof_trans = [
	0, 0, 0, 5, 0, 0, 0, 29, 
	30, 32, 34, 36, 36, 36, 36, 36, 
	36, 36, 36, 36, 36, 36, 36, 36, 
	36, 36, 36, 36, 36, 36, 36, 36, 
	36, 36, 36, 36, 36, 36, 36, 36, 
	65, 0
]

class << self
	attr_accessor :cpp_header_parser_start
end
self.cpp_header_parser_start = 6;
class << self
	attr_accessor :cpp_header_parser_first_final
end
self.cpp_header_parser_first_final = 6;
class << self
	attr_accessor :cpp_header_parser_error
end
self.cpp_header_parser_error = 0;

class << self
	attr_accessor :cpp_header_parser_en_c_comment
end
self.cpp_header_parser_en_c_comment = 4;
class << self
	attr_accessor :cpp_header_parser_en_main
end
self.cpp_header_parser_en_main = 6;


# line 59 "cpp_header_parser.rl"
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
      str << "#{indent}\tthis->#{@name}();\n"
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
    
# line 842 "cpp_header_parser.rb"
begin
	p ||= 0
	pe ||= data.length
	cs = cpp_header_parser_start
	ts = nil
	te = nil
	act = 0
end

# line 631 "cpp_header_parser.rl"
    
# line 854 "cpp_header_parser.rb"
begin
	_klen, _trans, _keys, _acts, _nacts = nil
	_goto_level = 0
	_resume = 10
	_eof_trans = 15
	_again = 20
	_test_eof = 30
	_out = 40
	while true
	_trigger_goto = false
	if _goto_level <= 0
	if p == pe
		_goto_level = _test_eof
		next
	end
	if cs == 0
		_goto_level = _out
		next
	end
	end
	if _goto_level <= _resume
	_acts = _cpp_header_parser_from_state_actions[cs]
	_nacts = _cpp_header_parser_actions[_acts]
	_acts += 1
	while _nacts > 0
		_nacts -= 1
		_acts += 1
		case _cpp_header_parser_actions[_acts - 1]
			when 4 then
# line 1 "NONE"
		begin
ts = p
		end
# line 888 "cpp_header_parser.rb"
		end # from state action switch
	end
	if _trigger_goto
		next
	end
	_keys = _cpp_header_parser_key_offsets[cs]
	_trans = _cpp_header_parser_index_offsets[cs]
	_klen = _cpp_header_parser_single_lengths[cs]
	_break_match = false
	
	begin
	  if _klen > 0
	     _lower = _keys
	     _upper = _keys + _klen - 1

	     loop do
	        break if _upper < _lower
	        _mid = _lower + ( (_upper - _lower) >> 1 )

	        if data[p].ord < _cpp_header_parser_trans_keys[_mid]
	           _upper = _mid - 1
	        elsif data[p].ord > _cpp_header_parser_trans_keys[_mid]
	           _lower = _mid + 1
	        else
	           _trans += (_mid - _keys)
	           _break_match = true
	           break
	        end
	     end # loop
	     break if _break_match
	     _keys += _klen
	     _trans += _klen
	  end
	  _klen = _cpp_header_parser_range_lengths[cs]
	  if _klen > 0
	     _lower = _keys
	     _upper = _keys + (_klen << 1) - 2
	     loop do
	        break if _upper < _lower
	        _mid = _lower + (((_upper-_lower) >> 1) & ~1)
	        if data[p].ord < _cpp_header_parser_trans_keys[_mid]
	          _upper = _mid - 2
	        elsif data[p].ord > _cpp_header_parser_trans_keys[_mid+1]
	          _lower = _mid + 2
	        else
	          _trans += ((_mid - _keys) >> 1)
	          _break_match = true
	          break
	        end
	     end # loop
	     break if _break_match
	     _trans += _klen
	  end
	end while false
	_trans = _cpp_header_parser_indicies[_trans]
	end
	if _goto_level <= _eof_trans
	cs = _cpp_header_parser_trans_targs[_trans]
	if _cpp_header_parser_trans_actions[_trans] != 0
		_acts = _cpp_header_parser_trans_actions[_trans]
		_nacts = _cpp_header_parser_actions[_acts]
		_acts += 1
		while _nacts > 0
			_nacts -= 1
			_acts += 1
			case _cpp_header_parser_actions[_acts - 1]
when 0 then
# line 25 "cpp_header_parser.rl"
		begin
 	begin
		cs = 6
		_trigger_goto = true
		_goto_level = _again
		break
	end
 		end
when 1 then
# line 46 "cpp_header_parser.rl"
		begin
 parser.token_begin(:number, p) 		end
when 2 then
# line 47 "cpp_header_parser.rl"
		begin
 parser.token_begin(:id, p) 		end
when 5 then
# line 1 "NONE"
		begin
te = p+1
		end
when 6 then
# line 28 "cpp_header_parser.rl"
		begin
act = 1;		end
when 7 then
# line 29 "cpp_header_parser.rl"
		begin
act = 2;		end
when 8 then
# line 30 "cpp_header_parser.rl"
		begin
act = 3;		end
when 9 then
# line 47 "cpp_header_parser.rl"
		begin
act = 18;		end
when 10 then
# line 31 "cpp_header_parser.rl"
		begin
te = p+1
 begin  parser.found_token(:public, p)  end
		end
when 11 then
# line 32 "cpp_header_parser.rl"
		begin
te = p+1
 begin  parser.found_token(:star, p)  end
		end
when 12 then
# line 34 "cpp_header_parser.rl"
		begin
te = p+1
 begin  parser.found_token(:comma, p)  end
		end
when 13 then
# line 35 "cpp_header_parser.rl"
		begin
te = p+1
 begin  parser.found_token(:semicolon, p)  end
		end
when 14 then
# line 36 "cpp_header_parser.rl"
		begin
te = p+1
 begin  parser.found_token(:open_bracket, p)  end
		end
when 15 then
# line 38 "cpp_header_parser.rl"
		begin
te = p+1
 begin  parser.found_token(:close_class, p)  end
		end
when 16 then
# line 39 "cpp_header_parser.rl"
		begin
te = p+1
 begin  parser.found_token(:open_parenthesis, p)  end
		end
when 17 then
# line 40 "cpp_header_parser.rl"
		begin
te = p+1
 begin  parser.found_token(:close_parenthesis, p)  end
		end
when 18 then
# line 41 "cpp_header_parser.rl"
		begin
te = p+1
 begin  parser.found_token(:ampersand, p)  end
		end
when 19 then
# line 42 "cpp_header_parser.rl"
		begin
te = p+1
 begin  parser.found_token(:equals, p)  end
		end
when 20 then
# line 43 "cpp_header_parser.rl"
		begin
te = p+1
 begin  parser.found_token(:ns_sep, p)  end
		end
when 21 then
# line 50 "cpp_header_parser.rl"
		begin
te = p+1
 begin  	begin
		cs = 4
		_trigger_goto = true
		_goto_level = _again
		break
	end
  end
		end
when 22 then
# line 51 "cpp_header_parser.rl"
		begin
te = p+1
		end
when 23 then
# line 33 "cpp_header_parser.rl"
		begin
te = p
p = p - 1; begin  parser.found_token(:colon, p)  end
		end
when 24 then
# line 37 "cpp_header_parser.rl"
		begin
te = p
p = p - 1; begin  parser.found_token(:close_bracket, p)  end
		end
when 25 then
# line 46 "cpp_header_parser.rl"
		begin
te = p
p = p - 1; begin  parser.found_token(:number, p)  end
		end
when 26 then
# line 47 "cpp_header_parser.rl"
		begin
te = p
p = p - 1; begin  parser.found_token(:id, p)  end
		end
when 27 then
# line 52 "cpp_header_parser.rl"
		begin
te = p
p = p - 1;		end
when 28 then
# line 47 "cpp_header_parser.rl"
		begin
 begin p = ((te))-1; end
 begin  parser.found_token(:id, p)  end
		end
when 29 then
# line 1 "NONE"
		begin
	case act
	when 1 then
	begin begin p = ((te))-1; end
 parser.found_token(:class, p) end
	when 2 then
	begin begin p = ((te))-1; end
 parser.found_token(:enum, p) end
	when 3 then
	begin begin p = ((te))-1; end
 parser.found_token(:static, p) end
	when 18 then
	begin begin p = ((te))-1; end
 parser.found_token(:id, p) end
end 
			end
# line 1130 "cpp_header_parser.rb"
			end # action switch
		end
	end
	if _trigger_goto
		next
	end
	end
	if _goto_level <= _again
	_acts = _cpp_header_parser_to_state_actions[cs]
	_nacts = _cpp_header_parser_actions[_acts]
	_acts += 1
	while _nacts > 0
		_nacts -= 1
		_acts += 1
		case _cpp_header_parser_actions[_acts - 1]
when 3 then
# line 1 "NONE"
		begin
ts = nil;		end
# line 1150 "cpp_header_parser.rb"
		end # to state action switch
	end
	if _trigger_goto
		next
	end
	if cs == 0
		_goto_level = _out
		next
	end
	p += 1
	if p != pe
		_goto_level = _resume
		next
	end
	end
	if _goto_level <= _test_eof
	if p == eof
	if _cpp_header_parser_eof_trans[cs] > 0
		_trans = _cpp_header_parser_eof_trans[cs] - 1;
		_goto_level = _eof_trans
		next;
	end
end
	end
	if _goto_level <= _out
		break
	end
	end
	end

# line 632 "cpp_header_parser.rl"
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
