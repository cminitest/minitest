#include <stdio.h>
#include "minitest.h"

describe("MiniTest") do
  it("exists 1") do
    //puts("test 1");
  end

  it("exists 2") do
    //puts("test 2");
  end

  context(".register_suite") do
    when("1") do
      it("registers a new suite") do
        //puts("test 4");
      end
    end

    when("2") do
      and("2.1") do
        it("chains the next suite") do
          //puts("test 5");
        end
      end

      and("2.2") do
        it("chains the next and previous suite") do
          //puts("test 6");
        end
      end
    end
  end

  context(".register_block") do
    given("a block has not had any IT blocks defined") do
      it("creates a new array with 1 element") do
        expect(1) to equal(1);
        expect(0) to not equal(1);
      end
    end
  end

  context(".step_back") do

  end

  context(".run") do

  end
end

int main() {
  minitest.run();
  return 0;
}