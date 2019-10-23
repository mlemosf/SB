#include "../include/exibidor.hpp"
#include "../include/cp_info.hpp"
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
	printf("This Class: \n", r.getThisClass());
	printf("Super Class: \n", r.getSuperClass());
	printf("This Class: %d\n", r.getThisClass());
	printf("Super Class: %d\n", r.getSuperClass());
	printf("Interfaces count: %d\n",r.getInterfacesCount());
	printf("Fields Count: %d\n",r.getFieldsCount());
	printf("Methods Count: %d\n",r.getMethodsCount());
	printf("Attributes Count: %d\n",r.getAttributesCount());
}

void Exibidor::ConstantPool()
{
	printf("\nConstantPool: \n\n");
	int qtd = r.getConstantPoolCount();
	for(int i = 0; i<qtd; i++){
		CONSTANT c = r.getConstantPoolElement(i);
		c.print();
	}
}

void Exibidor::Interfaces()
{
	printf("\nInterfaces: \n\n");
	/*
	int qtd = r.getInterfacesCount();
	vector<Interface_info> v = r.getInterfaces();
	for (int i = 0; i < qtd; ++i)
	{
		v[i].print();
	}*/
}

void Exibidor::Fields()
{
	printf("\nFields: \n\n");
	int qtd = r.getFieldsCount();
	vector<Field_info> v = r.getFields();
	for(int i =0;i<qtd;i++){
		v[i].print();
	}
}

void Exibidor::Methods()
{
	printf("\nMethods: \n\n");
	int qtd = r.getMethodsCount();
	vector<Method_info> v = r.getMethods();
	for (int i = 0; i < qtd; ++i)
	{
		v[i].print();
	}

}

void Exibidor::Attributes()
{
	printf("\nAttributes: \n\n");
	int qtd = r.getAttributesCount();
	vector<Attribute_info> v = r.getAttributes();
	for (int i = 0; i < qtd; ++i)
	{
		v[i].print();
	}
}