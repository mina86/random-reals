CXXFLAGS += -std=c++11


all: benchmark density

benchmark: benchmark.div benchmark.bits
density: density.div density.bits


run-benchmark: benchmark
	@echo; echo '*** Benchmark ***'; echo
	@echo '=== Using division ==='; time ./benchmark.div
	@echo '=== Using bit manipulations ==='; time ./benchmark.bits

run-density: density
	@echo; echo '*** Density ***'; echo
	@echo '=== Using division ==='; ./density.div
	@echo '=== Using bit manipulations ==='; ./density.bits

run-all: run-benchmark run-density


benchmark.%: CPPFLAGS+=-O3


%.div: %.cpp make-float.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.bits: %.cpp make-float.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -DUSE_BITS -o $@ $^ $(LDFLAGS)


clean:
	rm -f -- density.div density.bits benchmark.div benchmark.bits


.SUFFIXES:
.PHONY: clean benchmark density run-benchmark run-density run-all
