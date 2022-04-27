#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "MiniDictionary/MiniDictionary.h"

TEST_CASE("Should be returned translation of the words")
{
	Dictionary dictionary = {
		{ "cat", { "���", "�����" } },
		{ "ball", { "���" } }
	};

	REQUIRE(GetWordTranslations(dictionary, "cat") == WordTranslations{ "���", "�����" });
	REQUIRE(GetWordTranslations(dictionary, "ball") == WordTranslations{ "���" });
	REQUIRE(GetWordTranslations(dictionary, "meat") == WordTranslations{});
}

TEST_CASE("Should be returned translation of the phrases")
{
	Dictionary dictionary = {
		{ "great day", { "������� ����", "���������� ����" } },
		{ "the red square", { "������� �������" } }
	};

	REQUIRE(GetWordTranslations(dictionary, "great day") == WordTranslations{ "������� ����", "���������� ����" });
	REQUIRE(GetWordTranslations(dictionary, "The Red Square") == WordTranslations{ "������� �������" });
}

TEST_CASE("Should be returned translation of the phrases or words in any case")
{
	Dictionary dictionary = {
		{ "cat", { "���", "�����" } },
		{ "ball", { "���" } },
		{ "great day", { "������� ����", "���������� ����" } },
		{ "the red square", { "������� �������" } }
	};

	REQUIRE(GetWordTranslations(dictionary, "ThE ReD SqUaRe") == WordTranslations{ "������� �������" });
	REQUIRE(GetWordTranslations(dictionary, "BALL") == WordTranslations{ "���" });

	SECTION("Should be returned translation of the phrases or words in any case without losing the translation case")
	{
		REQUIRE(GetWordTranslations(dictionary, "GrEaT DaY") == WordTranslations{ "������� ����", "���������� ����" });
		REQUIRE(GetWordTranslations(dictionary, "CaT") == WordTranslations{ "���", "�����" });
	}
}

TEST_CASE("Should be returned reverse translation of the phrases or words")
{
	Dictionary dictionary = {
		{ "cat", { "���", "�����" } },
		{ "ball", { "���" } },
		{ "great day", { "������� ����", "���������� ����" } },
		{ "the red square", { "������� �������" } }
	};

	REQUIRE(GetWordTranslations(dictionary, "������� ����") == WordTranslations{ "great day" });
	REQUIRE(GetWordTranslations(dictionary, "���������� ����") == WordTranslations{ "great day" });
	REQUIRE(GetWordTranslations(dictionary, "���") == WordTranslations{ "cat" });
	REQUIRE(GetWordTranslations(dictionary, "�����") == WordTranslations{ "cat" });
	REQUIRE(GetWordTranslations(dictionary, "���") == WordTranslations{ "ball" });

	SECTION("Should be returned reverse translation of the phrases or words in any case")
	{
		dictionary = {
		{ "cat", { "���", "�����" } },
		{ "ball", { "���" } },
		{ "great day", { "������� ����", "���������� ����" } },
		{ "the red square", { "������� �������" } }
		};

		REQUIRE(GetWordTranslations(dictionary, "������� ����") == WordTranslations{ "great day" });
		REQUIRE(GetWordTranslations(dictionary, "���������� ����") == WordTranslations{ "great day" });
		REQUIRE(GetWordTranslations(dictionary, "���") == WordTranslations{ "cat" });
		REQUIRE(GetWordTranslations(dictionary, "�����") == WordTranslations{ "cat" });
		REQUIRE(GetWordTranslations(dictionary, "���") == WordTranslations{ "ball" });
	}
}

TEST_CASE("should be correctly add new words and phrases to the dictionary")
{
	Dictionary dictionary = {
		{ "cat", { "���" } },
		{ "ball", { "���" } },
		{ "the red square", { "������� �������" } }
	};

	AddTranslationInDictionary("�����", "cat", dictionary);
	AddTranslationInDictionary("evil cat", "������", dictionary);
	AddTranslationInDictionary("meet", "����", dictionary);

	Dictionary requiredDictionary = {
		{ "cat", { "���", "�����" }},
		{ "evil cat", { "������" }},
		{ "ball", { "���" } },
		{ "meet", { "����" } },
		{ "the red square", { "������� �������" } },
	};

	REQUIRE(dictionary == requiredDictionary);
}

