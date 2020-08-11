#include <gtest/gtest.h>

#include "utils.h"

extern "C" {
#include "lexer.h"
}

class TestLexer : public testing::Test {
protected:
    struct lexer *lexer;

    void SetUp() override {
        lexer = lx_init();
    }

    void TearDown() override {
        lx_destroy(lexer);
    }
};

/*
TEST_F(TestLexer, correctness)
{
    FILE* in = fmap_string("greet ; exit ;");

    lx_fill(lexer, in);

    ASSERT_EQ(lx_pop(lexer).type, TOK_GREET);
    ASSERT_EQ(lx_pop(lexer).type, TOK_SEMICOLON);
    ASSERT_EQ(lx_pop(lexer).type, TOK_EXIT);
    ASSERT_EQ(lx_pop(lexer).type, TOK_SEMICOLON);
}

TEST_F(TestLexer, correct_string)
{
    FILE* in = fmap_string("\"Hey\"");

    lx_fill(lexer, in);

    auto tok = lx_pop(lexer);

    ASSERT_EQ(tok.type, TOK_STRING);

    free(tok.arg);
}

TEST_F(TestLexer, correct_string_with_token_inside)
{
    FILE* in = fmap_string("\"add\"");

    lx_fill(lexer, in);

    auto tok = lx_pop(lexer);

    ASSERT_EQ(tok.type, TOK_STRING);

    free(tok.arg);
}

TEST_F(TestLexer, correct_integer)
{
    FILE* in = fmap_string("12");

    lx_fill(lexer, in);

    auto tok = lx_pop(lexer);

    ASSERT_EQ(tok.type, TOK_INTEGER);

    free(tok.arg);
}

TEST_F(TestLexer, correct_add)
{
    FILE* in = fmap_string("add");

    lx_fill(lexer, in);

    auto tok = lx_pop(lexer);

    ASSERT_EQ(tok.type, TOK_ADD);

    free(tok.arg);
}

TEST_F(TestLexer, correct_print)
{
    FILE* in = fmap_string("print");

    lx_fill(lexer, in);

    ASSERT_EQ(lx_pop(lexer).type, TOK_PRINT);
}

TEST_F(TestLexer, correct_semi)
{
    FILE* in = fmap_string(";");

    lx_fill(lexer, in);

    ASSERT_EQ(lx_pop(lexer).type, TOK_SEMICOLON);
}
*/

int main(int argc, char **argv)
{
    //testing::InitGoogleTest(&argc, argv);

    //return RUN_ALL_TESTS();
    return 0;
}
