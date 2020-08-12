#include <gtest/gtest.h>

#include "utils.h"

extern "C" {
#include "parser.h"
}

class TestParser : public testing::Test {
protected:
    struct parser *parser;
    struct lexer *lexer;

    void SetUp() override {
        lexer = lx_init();
        parser = pr_init(lexer);
    }

    void TearDown() override {
        pr_destroy(parser);
    }

    void pr_fill_lexer(std::string data) {
        auto in = fmap_string(data);

        lx_fill(parser->lexer, in);
    }
};

TEST_F(TestParser, correct)
{
    pr_fill_lexer("greet ; exit ; ");

    ASSERT_EQ(pr_parse(parser), 1);
}

/*
TEST_F(TestParser, invalid_print)
{
    pr_fill_lexer("print \"str1\" \"str2\"");

    ASSERT_EQ(pr_parse(parser), 0);
}

TEST_F(TestParser, add_not_enough_args)
{
    pr_fill_lexer("add 12");

    ASSERT_EQ(pr_parse(parser), 0);
}

TEST_F(TestParser, add_wrong_arg_type)
{
    pr_fill_lexer("add \"string\" exit");

    ASSERT_EQ(pr_parse(parser), 0);
}

TEST_F(TestParser, cmd_then_token)
{
    pr_fill_lexer("greet exit");

    ASSERT_EQ(pr_parse(parser), 0);
}
*/

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
