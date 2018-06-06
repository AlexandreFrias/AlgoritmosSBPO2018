CFLAGS= -Wall -m64 -g -w
CXX=clang++
HOME=/home/prof/Documentos/SBPO
ILOG=/opt/ibm/ILOG/CPLEX_Studio1263
CPPFLAGS= -DIL_STD -I$(ILOG)/cplex/include -I$(ILOG)/concert/include
CPLEXLIB=-L$(ILOG)/cplex/lib/x86-64_linux/static_pic -lilocplex -lcplex -L$(ILOG)/concert/lib/x86-64_linux/static_pic -lconcert -lm -lpthread
comp1:  
	$(CXX) $(CFLAGS) $(CPPFLAGS) -o mwnpp0 mwnpp0.cpp  $(CPLEXLIB)

comp2:  
	$(CXX) $(CFLAGS) $(CPPFLAGS) -o mwnpp1 mwnpp1.cpp  $(CPLEXLIB)

comp3:  
	$(CXX) $(CFLAGS) $(CPPFLAGS) -o mwnpp2 mwnpp2.cpp   $(CPLEXLIB)

comp4:  
	$(CXX) $(CFLAGS) $(CPPFLAGS) -o mwnpp3 mwnpp3.cpp  $(CPLEXLIB)

