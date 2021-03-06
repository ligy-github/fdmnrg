#.SILENT:
cc=icpc
name=fdmnrg.x
#name=work_dir/fdmnrg.x
#objects=main.o setup.o genoutput.o iterative_dia.o dos.o date_time.o deallocate.o func_wn.o
#objects=main.o setup.o genoutput.o iterative_dia.o dos2.o date_time.o deallocate.o func_wn.o
objects=main.o setup.o genoutput.o iterative_dia_band.o iterative_dia_total.o dos.o date_time.o func_wn.o thermal_dynamic_quantity.o #deallocate.o

#CPPFLAGS=-O0 -g
#CPPFLAGS=-O3
MKL_FLAGS=-mkl=parallel
OPENMP_FLAGS=-qopenmp

$(name): $(objects)
	$(cc) $(CPPFLAGS) $(MKL_FLAGS) $(OPENMP_FLAGS) -o $(name) $(objects)

main.o: main.cpp
	$(cc)  $(CPPFLAGS) -c main.cpp

setup.o: setup.cpp struct.h
	$(cc)  $(CPPFLAGS) -c setup.cpp

genoutput.o: genoutput.cpp setup.h
	$(cc)  $(CPPFLAGS) -c genoutput.cpp

date_time.o: date_time.cpp
	$(cc)  $(CPPFLAGS) -c date_time.cpp

iterative_dia_band.o: iterative_dia_band.cpp setup.h struct.h
	$(cc)  $(CPPFLAGS)  $(MKL_FLAGS) $(OPENMP_FLAGS) -c iterative_dia_band.cpp

iterative_dia_total.o: iterative_dia_total.cpp setup.h struct.h
	$(cc)  $(CPPFLAGS)  $(MKL_FLAGS) $(OPENMP_FLAGS) -c iterative_dia_total.cpp

func_wn.o: func_wn.cpp setup.h struct.h
	$(cc)  $(CPPFLAGS) $(OPENMP_FLAGS) -c func_wn.cpp

dos.o: dos.cpp setup.h struct.h
	$(cc)  $(CPPFLAGS) $(MKL_FLAGS) $(OPENMP_FLAGS) -c dos.cpp

# deallocate.o: deallocate.cpp setup.h struct.h
# 	$(cc)  $(CPPFLAGS)  -c deallocate.cpp

thermal_dynamic_quantity.o: thermal_dynamic_quantity.cpp setup.h struct.h
	$(cc)  $(CPPFLAGS)  -c thermal_dynamic_quantity.cpp

clean:
	rm $(objects)
