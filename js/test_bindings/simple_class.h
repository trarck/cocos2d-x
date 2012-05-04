#include <string>

class SimpleNativeClass
{
protected:
	int m_someField;
	int m_someOtherField;
	char* m_anotherMoreComplexField;

public:
	SimpleNativeClass();
	~SimpleNativeClass();

	int getSomeField();
	int getSomeOtherField();
	char *getAnotherMoreComplexField();
	void setSomeField(int f);
	void setSomeOtherField(int f);
	void setAnotherMoreComplexField(const char *str);

	// std::string not working yet!
	int doSomeProcessing(std::string arg1, std::string arg2);
};
