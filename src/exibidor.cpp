#include "../include/exibidor.hpp"
using namespace std;

Exibidor::Exibidor(Leitor l)
{
	r = l;
}

void Exibidor::GeneralInformation()
{
	printf("Minor version: %x\n", r.getMinorVersion());
	printf("Major version: %x\n", r.getMajorVersion());
	printf("Constant pool count: %d\n", r.getConstantPoolCount());
	printf("Acess Flags: %x\n", r.getAcessFlags());
	printf("This Class: ");
	printf("Super Class: ");
	printf("Interfaces count: %d\n",r.getInterfacesCount());
	printf("Fields Count: %d\n",r.getFieldsCount());
	printf("Methods Count: %d\n",r.getMethodsCount());
	printf("Attributes Count: %d\n",r.getAttributesCount());
}

void Exibidor::ConstantPool()
{
	
}

void Exibidor::Interfaces()
{

}

void Exibidor::Fields()
{
	printf("Show Fields:\n");
	printf("Public:%d\nPrivate:%d\nProtected:%d\nStatic:%d\nFinal:%d\nVolatile:%d\nTransient:%d\nSynthetic:%d\nEnum:%d\nAll:%d\n",
		PUBLIC,PRIVATE,PROTECTED,STATIC,FINAL,VOLATILE,TRANSIENT,SYNTHETIC,ENUM,ALL);
	scanf("%d\n",&show);

	switch(show){
		case PUBLIC:
		  break;
		case PRIVATE:
		  break;
		case PROTECTED:
		  break;
		case STATIC:
		  break;
		case FINAL:
		  break;
		case VOLATILE:
		  break;
		case TRANSIENT:
		  break;
		case SYNTHETIC:
		  break;
		case ENUM:
		  break;
		case ALL:
		  break;
	}

}

void Exibidor::ShowField(Typeshow s = ALL)
{
	//printf()
}

void Exibidor::Methods()
{

}

void Exibidor::Attributes()
{

}