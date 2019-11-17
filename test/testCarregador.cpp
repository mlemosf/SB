#define CATCH_CONFIG_MAIN
#include "header/catch.hpp"
#include "../include/leitor.hpp"
#include "../include/fieldinfo.hpp"
#include "../include/attribute_info.hpp"

TEST_CASE("Leitor responsável por ler os dados do .class","[Leitor]"){
	Leitor* l = new Leitor();
	SECTION("Arquivo é lido pela função loadFile"){
		l->loadFile("teste.class");
		REQUIRE(sizeof(l->byte_array) == 504);
	
		l->loadFile("");
		REQUIRE(sizeof(l->byte_array) == 0);
	}
	SECTION("Diferentes tamanhos podem ser lidos do arquivo"){
		l->loadFile("teste.class");
		REQUIRE(sizeof(l->read1byte()) == 1);
		REQUIRE(sizeof(l->read2byte()) == 2);
		REQUIRE(sizeof(l->read4byte()) == 4);
	}
	SECTION("Dados do arquivo podem ser setados na classe")
	{
		l->loadFile("teste.class");
		REQUIRE(l->SetMagicNumber() == true);
		REQUIRE(l->SetMinorVersion() == true);
		REQUIRE(l->SetMajorVersion() == true);
		REQUIRE(l->SetConstantPool() == true);
		REQUIRE(l->SetAcessFlags() == true);
		REQUIRE(l->SetThisClass() == true);
		REQUIRE(l->SetSuperClass() == true);
		REQUIRE(l->SetInterfacesCount() == true);
		REQUIRE(l->SetFieldsCount() == true);
		REQUIRE(l->SetFields() == true);
		REQUIRE(l->SetMethodsCount() == true);
		REQUIRE(l->SetAttributesCount() == true);
		REQUIRE(l->SetAttributes() == true);
	}

}
