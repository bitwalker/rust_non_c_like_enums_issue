#include <stdio.h>
#include <stdint.h>

extern "C" {

enum class TypeTag : uint32_t {
  Unknown = 0,
  Tuple,
};

struct TypeAny { TypeTag tag; };
struct TypeTuple { TypeTag tag; uint32_t arity; };

union Type {
  TypeAny any;
  TypeTuple tuple;
};

struct Type2Tuple { uint32_t arity; };

struct Type2 {
    TypeTag tag;
    union {
        Type2Tuple tuple;
    };
};

bool RunTest1(Type t) {
  printf("Running test 1..\n");
  printf("Tag = %d\n", t.any.tag);
  if (t.any.tag == TypeTag::Tuple) {
    printf("Arity = %d\n", t.tuple.arity);
    return true;
  }
  return false;
}

bool RunTest2(Type2 t) {
  printf("Running test 2..\n");
  printf("Tag = %d\n", t.tag);
  if (t.tag == TypeTag::Tuple) {
    printf("Arity = %d\n", t.tuple.arity);
    return true;
  }
  return false;
}

bool RunTest3(Type *t) {
  printf("Running test 3..\n");
  printf("Tag = %d\n", t->any.tag);
  if (t->any.tag == TypeTag::Tuple) {
    printf("Arity = %d\n", t->tuple.arity);
    return true;
  }
  return false;
}

bool RunTest4(Type2 *t) {
  printf("Running test 4..\n");
  printf("Tag = %d\n", t->tag);
  if (t->tag == TypeTag::Tuple) {
    printf("Arity = %d\n", t->tuple.arity);
    return true;
  }
  return false;
}

}
