
# Makefile for Rubik's Cube tools

PROGSRC=$(wildcard src/[a-z]*.cpp)
PROGOBJ=$(subst .cpp,.o,$(PROGSRC))
PROGBIN=$(addprefix bin/,$(notdir $(subst .o,,$(PROGOBJ))))

LIBSRC=$(wildcard src/[A-Z]*.cpp)
LIBOBJ=$(subst .cpp,.o,$(LIBSRC))

TESTSRC=$(wildcard test/*.cpp)
TESTOBJ=$(subst .cpp,.o,$(TESTSRC))
TESTBIN=$(subst .o,,$(TESTOBJ))

INCLUDE=-Iinclude
LIBRARY=lib/rubik.a

COMMONFLAGS=-std=c++11
CXXFLAGS=-O3 -DNDEBUG $(COMMONFLAGS)
DEBUGFLAGS=-g $(COMMONFLAGS)

DEPDIR:=.d
$(shell mkdir -p $(DEPDIR)/src $(DEPDIR)/test)
DEPFLAGS=-MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMP=mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

all: $(PROGBIN) $(TESTBIN)

bin lib:
	mkdir $@

clean:
	rm -f $(PROGOBJ) $(PROGBIN) $(LIBOBJ) $(LIBRARY) $(TESTOBJ) $(TESTBIN)

reallyclean: clean
	rm -rf $(DEPDIR)

debug:
	$(MAKE) CXXFLAGS='$(DEBUGFLAGS)' clean all

test: $(TESTBIN)
	@for t in $(TESTBIN); do \
		echo "Running $$t" && \
		$$t; \
	done

$(PROGOBJ) : %.o : %.cpp $(DEPDIR)/%.d
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) $(INCLUDE) -c $< -o $@
	$(POSTCOMP)
    
$(PROGBIN) : bin/% : src/%.o $(LIBRARY) | bin
	$(CXX) $(CXXFLAGS) $< $(LIBRARY) -o $@

$(LIBOBJ) : %.o : %.cpp $(DEPDIR)/%.d
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) $(INCLUDE) -c $< -o $@
	$(POSTCOMP)

$(LIBRARY) : $(LIBOBJ) | lib
	$(AR) rvs $(LIBRARY) $(LIBOBJ)

$(TESTOBJ) : %.o : %.cpp $(DEPDIR)/%.d
	$(CXX) $(DEBUGFLAGS) $(DEPFLAGS) $(INCLUDE) -c $< -o $@
	$(POSTCOMP)
    
$(TESTBIN) : % : %.o $(LIBRARY)
	$(CXX) $(DEBUGFLAGS) $< $(LIBRARY) -o $@

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(PROGSRC) $(LIBSRC) $(TESTSRC)))

