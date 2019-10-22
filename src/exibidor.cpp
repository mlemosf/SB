#include "../include/exibidor.hpp"
using namespace std;

Exibidor::Exibidor(Leitor l)
{
	r = l;
}

void Exibidor::Mostrar()
{
	system(CLS);
	GeneralInformation();
	ConstantPool();
	Interfaces();
	Fields();
	Methods();
}

void Exibidor::GeneralInformation()
{
	printf("\nGeneral Information: \n\n");
	printf("Minor version: %x\n", r.getMinorVersion());
	printf("Major version: %x\n", r.getMajorVersion());
	printf("Constant pool count: %d\n", r.getConstantPoolCount());
	printf("Acess Flags: %x\n", r.getAcessFlags());
	printf("This Class: \n");
	printf("Super Class: \n");
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
	printf("\nInterfaces: \n\n");
}

void Exibidor::Fields()
{
	printf("\nFields: \n\n");
	/*fazer um loop para cada field e ir exibindo esses atributos com o filtro correspondente*/
	printf("Name:\n");
	printf("Descriptor:\n");
	printf("AcessFlags:\n");
}

void Exibidor::Methods()
{
	printf("\nMethods: \n\n");
	printf("Name:\n");
	printf("Descriptor:\n");
	printf("AcessFlags:\n");
}

void Exibidor::Attributes()
{
	printf("\nAttributes: \n\n");
}