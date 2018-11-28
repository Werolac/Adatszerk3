//============================================================================
// Name        : 3Hazi.cpp
// Author      : veroczki
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

// your solution comes here
#include "rope.hpp"
#include"textEditor.hpp"
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

struct test_controller {
	bool enabled;
	std::string label;
	int points;
	bool ok;
	bool run;
	int &out;
	test_controller(bool enabled, std::string &&label, int points, int &out) :
			enabled(enabled), label(std::move(label)), points(points), ok(true), run(
					true), out(out) {
		if (enabled) {
			std::cout << ">>> Test: " << this->label << " (" << points << ")"
					<< std::endl;
		}
	}
	~test_controller() {
		if (enabled) {
			out += ok ? points : 0;
			std::cout << ">>> Result: " << (ok ? "PASS" : "FAIL") << std::endl;
		}
	}
};

struct measurement_controller {
	std::string name;
	std::chrono::nanoseconds &out;
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	bool run;
	measurement_controller(std::string &&name, std::chrono::nanoseconds &out) :
			name(std::move(name)), out(out), start(
					std::chrono::high_resolution_clock::now()), run(true) {
	}
	~measurement_controller() {
		auto stop = std::chrono::high_resolution_clock::now();
		out = std::chrono::duration_cast<std::chrono::nanoseconds>(
				stop - start);
		std::cout << name << ": " << out.count() << "ns" << std::endl;
	}
};

#define TEST(label, points)                                                    \
  for (test_controller cntr(++counter == test_no || test_no == 0, label,       \
                            points, total);                                    \
       cntr.run; cntr.run = false)

#define CHECK_EQ(val, expr)                                                    \
  if (cntr.ok) {                                                               \
    try {                                                                      \
      cntr.ok = val == (expr);                                                 \
    } catch (...) {                                                            \
      cntr.ok = false;                                                         \
      std::cout << ">>> unexpected exception" << std::endl;                    \
    }                                                                          \
    if (!cntr.ok) {                                                            \
      std::cout << ">>> " << #val << " == " << #expr << " failed at "          \
                << __LINE__ << " Expr result: " << (expr) << std::endl;        \
    }                                                                          \
  }

int main(int argc, char *argv[]) {
	int test_no = 0;
	int counter = 0;
	int total = 0;
	srand(time(nullptr));
	if (argc == 2) {
		test_no = std::atoi(argv[1]);
	}

	TEST("Create an empty tree. Length should be 0.", 2)
	{
		Rope rope;
		CHECK_EQ(0, rope.length());
	}
	/*
	 TEST("Create a non empty tree. Text should be the same.", 3) {
	 Rope rope("The quick brown fox jumps over the lazy dog.");
	 CHECK_EQ("The quick brown fox jumps over the lazy dog.", rope.report(0, 43));
	 }

	 TEST("Create a TextEditor and add a few elements. Length should grow.", 5) {
	 TextEditor texteditor("The");
	 CHECK_EQ(3, texteditor.length());
	 texteditor.insert(" quick");
	 CHECK_EQ(9, texteditor.length());
	 texteditor.insert(" brown fox jumps over the lazy dog.");
	 CHECK_EQ(44, texteditor.length());
	 }

	 TEST("Create a TextEditor and add a few elements. Elements should be in the tree, should get them using ctrlF().", 10) {
	 TextEditor texteditor;
	 texteditor.insert("Adatszerkezetek");
	 texteditor.insert("ĂŠs");
	 texteditor.insert("algoritmusok");
	 texteditor.insert(".:)");
	 CHECK_EQ(false, texteditor.ctrlF("Adat").empty());
	 CHECK_EQ(false, texteditor.ctrlF("ritmusok").empty());
	 CHECK_EQ(false, texteditor.ctrlF(":)").empty());
	 CHECK_EQ(true, texteditor.ctrlF("AnalĂ­zis").empty());
	 CHECK_EQ(true, texteditor.ctrlF("InformĂĄciĂłtechnika ĂŠs bionika fizikai alapjai I.").empty());
	 CHECK_EQ(true, texteditor.ctrlF(":(").empty());
	 }

	 TEST("Create a TextEditor. Test moving cursor, selection and report.", 5) {
	 TextEditor texteditor("PĂĄzmĂĄny PĂŠter Katolikus Egyetem, InformĂĄciĂłs TechnolĂłgiai ĂŠs Bionika Kar");
	 texteditor.moveCursor(0);
	 texteditor.select(7);
	 CHECK_EQ("PĂĄzmĂĄny", texteditor.report());
	 texteditor.stepLeft();
	 texteditor.stepRight();
	 CHECK_EQ("", texteditor.report());
	 texteditor.moveCursor(123456789);
	 texteditor.select(0);
	 CHECK_EQ("P", texteditor.report());
	 }

	 TEST("Test deletion. Size should shrink and text should disappear.", 10) {
	 TextEditor texteditor("TEst dEleTIon. sIZe SHouLd ShRInK.");
	 CHECK_EQ(false, texteditor.ctrlF("st ").empty());
	 texteditor.select(27);
	 texteditor.remove();
	 CHECK_EQ(27, texteditor.length());
	 CHECK_EQ(true, texteditor.ctrlF("ShRInk").empty());
	 texteditor.ctrlA();
	 CHECK_EQ("TEst dEleTIon. sIZe SHouLd ", texteditor.report());
	 texteditor.moveCursor(0);
	 texteditor.select(4);
	 texteditor.remove();
	 CHECK_EQ(23, texteditor.length());
	 CHECK_EQ(true, texteditor.ctrlF("TEst").empty());
	 texteditor.ctrlA();
	 CHECK_EQ(" dEleTIon. sIZe SHouLd ", texteditor.report());
	 texteditor.ctrlA();
	 texteditor.remove();
	 CHECK_EQ(0, texteditor.length());
	 }

	 TEST("Test more complicated text editing.", 15) {
	 TextEditor texteditor;
	 texteditor.insert("ez a hĂĄzi feladat.");
	 texteditor.moveCursor(0);
	 texteditor.insert("RemĂŠlem, hogy");
	 texteditor.insert(" nagyon rosszul ");
	 texteditor.insert("fog sikerĂźlni ");
	 vector<unsigned int> rosszulIndexek = texteditor.ctrlF("rosszul");
	 texteditor.moveCursor(rosszulIndexek[0]);
	 texteditor.select(rosszulIndexek[0]+7);
	 texteditor.insert("jĂłl");
	 vector<unsigned int> haziIndexek = texteditor.ctrlF("hĂĄzi feladat");
	 texteditor.moveCursor(haziIndexek[0]);
	 texteditor.select(haziIndexek[0]+12);
	 texteditor.ctrlC();
	 texteditor.moveCursor(texteditor.length()-2);
	 texteditor.insert(" ĂŠs az Ăśsszes tĂśbbi ");
	 texteditor.ctrlV();
	 texteditor.insert(" is");
	 texteditor.ctrlA();
	 CHECK_EQ("RemĂŠlem, hogy nagyon jĂłl fog sikerĂźlni ez a hĂĄzi feladat ĂŠs az Ăśsszes tĂśbbi hĂĄzi feladat is.", texteditor.report());
	 texteditor.ctrlX();
	 CHECK_EQ("", texteditor.report());
	 texteditor.ctrlV();
	 CHECK_EQ("RemĂŠlem, hogy nagyon jĂłl fog sikerĂźlni ez a hĂĄzi feladat ĂŠs az Ăśsszes tĂśbbi hĂĄzi feladat is.", texteditor.report());
	 }

	 std::cout << ">>> TOTAL POINTS: " << total << std::endl;*/
	return 0;
}
