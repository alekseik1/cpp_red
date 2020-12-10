#include <string>
#include <list>
#include "test_runner.h"
using namespace std;

class Editor {
 public:
  // Реализуйте конструктор по умолчанию и объявленные методы
  Editor(): _text({}), _buffer({}), _cursor(_text.begin()) {}
  void Left() { if (_cursor != _text.begin()) --_cursor; }
  void Right() { if (_cursor != _text.end()) ++_cursor; }
  void Insert(char token) { _cursor = ++(_text.insert(_cursor, token)); }
  void Cut(size_t tokens = 1) {
      auto end = moveCursor(tokens);
      _buffer.clear();
      _buffer.splice(_buffer.begin(), _text, _cursor, end);
      _cursor = end;
  }
  void Copy(size_t tokens = 1) {
      _buffer.clear();
      _buffer.insert(_buffer.begin(), _cursor, moveCursor(tokens));
  }
  void Paste() {
      _text.insert(_cursor, _buffer.begin(), _buffer.end());
  }
  string GetText() const { return string(_text.begin(), _text.end()); }
private:
    list<char> _text, _buffer;
    list<char>::iterator _cursor;

    list<char>::iterator moveCursor(size_t n) {
        auto result = _cursor;
        for (; (n != 0) && (result != _text.end()); --n) ++result;
        return result;
    }
};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);
    
    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;
    
    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();
    
    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }
  
  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");
  
  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  return 0;
}