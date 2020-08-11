#include <gtest/gtest.h>

extern "C" {
#include "tok_vec.h"
}

#define BASE_TOKEN(Name, Type) static struct token Name = { .type = Type, .arg = NULL }

//BASE_TOKEN(greet, TOK_GREET);
//BASE_TOKEN(error, TOK_ERROR);
//BASE_TOKEN(semicolon, TOK_SEMICOLON);
//BASE_TOKEN(integer, TOK_INTEGER);

#define ASSERT_TOKEQ(Lhs, Rhs)         \
    do {                               \
        struct token tmp = Lhs;        \
        ASSERT_EQ(tmp.type, Rhs.type); \
        ASSERT_EQ(tmp.arg, Rhs.arg);   \
    } while (0)

class TvTesting : public testing::Test {
protected:
    struct tok_vec *vec;

    void SetUp() override {
        vec = tv_init();
    }

    void TearDown() override {
        tv_destroy(vec);
    }
};

TEST_F(TvTesting, default_values)
{
    ASSERT_EQ(vec->capacity, TV_DEFAULT_CAPACITY);
    ASSERT_EQ(vec->size, 0);
}
/*
TEST_F(TvTesting, pop_empty)
{
    ASSERT_TOKEQ(tv_pop_front(vec), error);
}

TEST_F(TvTesting, pop_correct)
{
    ASSERT_EQ(tv_push_back(vec, greet), 1);
    ASSERT_TOKEQ(tv_pop_front(vec), greet);
    ASSERT_TOKEQ(tv_pop_front(vec), error);
}

TEST_F(TvTesting, peek_correct)
{
    ASSERT_EQ(tv_push_back(vec, greet), 1);
    ASSERT_EQ(tv_peek(vec), TOK_GREET);
    ASSERT_EQ(tv_peek(vec), TOK_GREET);
    ASSERT_TOKEQ(tv_pop_front(vec), greet);
}

TEST_F(TvTesting, push_order)
{
    ASSERT_EQ(tv_push_back(vec, greet), 1);
    ASSERT_EQ(tv_push_back(vec, semicolon), 1);
    ASSERT_EQ(tv_push_back(vec, integer), 1);

    ASSERT_TOKEQ(tv_pop_front(vec), greet);
    ASSERT_TOKEQ(tv_pop_front(vec), semicolon);
    ASSERT_TOKEQ(tv_pop_front(vec), integer);
}

TEST_F(TvTesting, push_string)
{
    char *buff = (char *) calloc(12, 1);
    memcpy(buff, "Hey there !\0", 12);
    struct token str = { .type = TOK_STRING, .arg = buff };

    ASSERT_EQ(tv_push_back(vec, str), 1);
    ASSERT_TOKEQ(tv_pop_front(vec), str);

    free(buff);
}

TEST_F(TvTesting, push_int)
{
    int *buff = (int *) calloc(1, sizeof(int));
    *buff = 864;
    struct token i = { .type = TOK_INTEGER, .arg = buff };

    ASSERT_EQ(tv_push_back(vec, i), 1);
    ASSERT_TOKEQ(tv_pop_front(vec), i);

    free(buff);
}
*/
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
