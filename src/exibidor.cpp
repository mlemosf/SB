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