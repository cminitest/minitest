#include "minitest/minitest.h"

void mockSuite() {}

describe("MiniTest Core", minitest_core)
  it("is registered")
    expect(1) to equal(1)
  end
end