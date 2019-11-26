#include "../include/exibidor.hpp"
#include "../include/cp_info.hpp"
using namespace std;

/*Exibidor::Exibidor(Leitor l)
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
*/
/*
void Exibidor::GeneralInformation()
{
	printf("\nGeneral Information: \n\n");
	printf("Minor version: %x\n", r.get(MINOR_VERSION));
	printf("Major version: %x\n", r.get(MAJOR_VERSION));
	printf("Constant pool count: %d\n", r.get(CONSTANT_POOL_COUNT));
	printf("Acess Flags: %x\n", r.get(ACCESS_FLAGS));
	printf("This Class: %d\n", r.get(THIS_CLASS));
	printf("Super Class: %d\n", r.get(SUPER_CLASS));
	printf("Interfaces count: %d\n",r.get(INTERFACES_COUNT));
	printf("Fields Count: %d\n",r.get(FIELDS_COUNT));
	printf("Methods Count: %d\n",r.get(METHODS_COUNT));
	printf("Attributes Count: %d\n",r.get(ATTRIBUTES_COUNT));
}

void Exibidor::ConstantPool()
{
	printf("\nConstantPool: \n\n");
	u2 qtd = r.get(CONSTANT_POOL_COUNT);
	for(u2 i = 0; i<qtd; i++){
		//CONSTANT c = r.getConstantPoolElement(i);
		//c.print();
	}
}
*/

/*void Exibidor::Interfaces()
{
	printf("\nInterfaces: \n\n");

}*/
/*
void Exibidor::Fields()
{
	printf("\nFields: \n\n");
	int qtd = r.get(FIELDS_COUNT);
	vector<Field_info> v = r.getFields();
	for(int i =0;i<qtd;i++){
		v[i].print();
	}
}

void Exibidor::Methods()
{
	printf("\nMethods: \n\n");
	int qtd = r.get(METHODS_COUNT);
	vector<Method_info> v = r.getMethods();
	for (int i = 0; i < qtd; ++i)
	{
		v[i].print();
	}

}

void Exibidor::Attributes()
{
	printf("\nAttributes: \n\n");
	int qtd = r.get(ATTRIBUTES_COUNT);
	vector<Attribute_info> v = r.getAttributes();
	for (int i = 0; i < qtd; ++i)
	{
		v[i].print();
	}
}*/