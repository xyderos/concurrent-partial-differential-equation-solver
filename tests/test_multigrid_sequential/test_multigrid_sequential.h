#include <cppunit/extensions/HelperMacros.h>

class test_multigrid_sequential : public CPPUNIT_NS::TestCase {

    private:
	CPPUNIT_TEST_SUITE(test_multigrid_sequential);
	CPPUNIT_TEST(test_case_one);
	CPPUNIT_TEST(test_case_two);
	CPPUNIT_TEST_SUITE_END();

    public:
	void setUp() override { }
	void tearDown() override { }

    protected:
	void test_case_one();
	void test_case_two();
};

CPPUNIT_TEST_SUITE_REGISTRATION(test_multigrid_sequential);
