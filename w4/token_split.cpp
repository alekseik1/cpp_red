#include "test_runner.h"

#include <iterator>
#include <utility>
#include <vector>

using namespace std;

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template <typename Token>
using Sentence = vector<Token>;

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
    // Напишите реализацию функции, не копируя объекты типа Token
    vector<Sentence<Token>> result;
    vector<Token> tmp;
    bool do_count = false;
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        bool is_punct = it->IsEndSentencePunctuation();
        if (is_punct) do_count = true;
        if (!is_punct && do_count) {
            // End of Sentence
            do_count = false;
            result.push_back(move(tmp));
            tmp.clear();
            tmp.push_back(move(*it));
        } else if (is_punct) {
            tmp.push_back(move(*it));
        } else {
            tmp.push_back(move(*it));
        }
        if (next(it) == tokens.end()) {
            result.push_back(move(tmp));
        }
    }
    return result;
}


struct TestToken {
    string data;
    bool is_end_sentence_punctuation = false;

    bool IsEndSentencePunctuation() const {
        return is_end_sentence_punctuation;
    }
    bool operator==(const TestToken& other) const {
        return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
    }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
    return stream << token.data;
}

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting() {
    ASSERT_EQUAL(
            SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
            vector<Sentence<TestToken>>({
                                                {{"Split"}, {"into"}, {"sentences"}, {"!"}}
                                        })
    );

    ASSERT_EQUAL(
            SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
            vector<Sentence<TestToken>>({
                                                {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
                                        })
    );

    ASSERT_EQUAL(
            SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
            vector<Sentence<TestToken>>({
                                                {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
                                                {{"Without"}, {"copies"}, {".", true}},
                                        })
    );
}

void TestEmpty() {
    ASSERT_EQUAL(
            SplitIntoSentences(vector<TestToken>({})),
            vector<Sentence<TestToken>>({})
    );
}

void TestSignBeforeEnd() {
    ASSERT_EQUAL(
            SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"Hello"}})),
            vector<Sentence<TestToken>>({
                                                {{"Split"}, {"into"}, {"sentences"}, {"!", true}},
                                                {{"Hello"}}
                                        })
    );
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSplitting);
    RUN_TEST(tr, TestEmpty);
    RUN_TEST(tr, TestSignBeforeEnd);
    return 0;
}