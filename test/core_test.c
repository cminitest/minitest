#include "minitest/minitest.h"

void mockSuite() {}

describe("MiniTest Core", minitest_core)

  MiniTest subject = {
    .assertions = 0,
    .test_cases = 0,
    .passes = 0,
    .failures = 0,
    .register_suite = mt->register_suite,
    .register_block = mt->register_block,
    .step_back      = mt->step_back,
    .clear          = mt->clear
  };

  context("core")
    context(".register_suite")
      subject.register_suite(&subject, "MockSuite", mockSuite);

      it("adds the suite to the suites list")
        expect(subject.current->name) to equal("MockSuite")
      end

      it("sets a root block as the current block")
        expect(subject.current->current_block->block_type) to equal(ROOT_TYPE)
      end
    end

    context(".register_block")
      when("the block is not an IT clause")
        subject.register_block(CONTEXT_TYPE, &subject, "Mock Context");

        it("adds the block to the children")
          expect(subject.current->current_block->previous->children.used) to equal(1)
        end

        it("sets the current block to the newly registered block")
          expect(subject.current->current_block->name) to equal("Mock Context")
        end
      end

      when("the block is an IT clause")
        subject.register_block(IT_TYPE, &subject, "Mock It Clause");

        it("adds the block to the it_blocks")
          expect(subject.current->current_block->it_blocks.used) to equal(1)
        end

        it("sets the it_flag")
          expect(subject.current->it_flag) to equal(1)
        end
      end
    end

    context(".step_back")
      when("the block is not an IT clause")
        subject.register_block(CONTEXT_TYPE, &subject, "Mock Context 2");
        subject.current->it_flag = 0;

        it("steps back to the previous block")
          void* previous = subject.current->current_block;
          subject.step_back(&subject);
          void* current = subject.current->current_block;

          expect(previous) to not equal(current)
        end
      end

      when("the block is an IT clause")
        subject.register_block(IT_TYPE, &subject, "Mock It Clause");

        it("does not step back from the current block")
          void* previous = subject.current->current_block;
          subject.step_back(&subject);
          void* current = subject.current->current_block;

          expect(previous) to equal(current)
        end
      end    
    end

    context(".clear")
      /*

      TODO: this causes a segment fault on windows

      subject.clear(&subject);

      it("clears the test suite")
        expect((void*)subject.suites) to equal(NULL)
        expect((void*)subject.current) to equal(NULL)
        expect(subject.assertions) to equal(0)
        expect(subject.test_cases) to equal(0)
        expect(subject.passes) to equal(0)
        expect(subject.failures) to equal(0)
      end
      */
    end
  end
end