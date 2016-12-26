CXXFLAGS += -std=c++11


all: benchmark density

benchmark: bin/benchmark.div bin/benchmark.bits
density: bin/density.div bin/density.bits


run-benchmark: benchmark
	@echo; echo '*** Benchmark ***'; echo
	@echo '=== Using division ==='; time ./bin/benchmark.div
	@echo '=== Using bit manipulations ==='; time ./bin/benchmark.bits

run-density: density
	@echo; echo '*** Density ***'; echo
	@echo '=== Using division ==='; ./bin/density.div
	@echo '=== Using bit manipulations ==='; ./bin/density.bits

run-all: run-benchmark run-density


bin/benchmark.%: CPPFLAGS+=-O3


bin/%.div: src/%.cpp src/make-float.h
	@mkdir -p -- $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

bin/%.bits: src/%.cpp src/make-float.h
	@mkdir -p -- $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -DUSE_BITS -o $@ $^ $(LDFLAGS)


clean:
	[ ! -d bin ] || rm -r -- bin


.SUFFIXES:
.PHONY: clean benchmark density run-benchmark run-density run-all
