#include <cppunit/extensions/HelperMacros.h>

class test_jacobi_concurrent : public CPPUNIT_NS::TestCase {

    private:
	CPPUNIT_TEST_SUITE(test_jacobi_concurrent);
	CPPUNIT_TEST(test_case_one);
	CPPUNIT_TEST(test_case_two);
	CPPUNIT_TEST(test_case_three);
	CPPUNIT_TEST(test_case_four);
	CPPUNIT_TEST(test_case_five);
	CPPUNIT_TEST(test_case_six);
	CPPUNIT_TEST(test_case_seven);
	CPPUNIT_TEST(test_case_eight);
	CPPUNIT_TEST_SUITE_END();

    public:
	void setUp() override { }
	void tearDown() override { }

    protected:
	void test_case_one();
	void test_case_two();
	void test_case_three();
	void test_case_four();
	void test_case_five();
	void test_case_six();
	void test_case_seven();
	void test_case_eight();
};

CPPUNIT_TEST_SUITE_REGISTRATION(test_jacobi_concurrent);
