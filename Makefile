#------------------------------------------------------------------------------
SOURCE=main.cpp point.h cluster.h kmeans.h kmeans.cpp
MYPROGRAM=KMeans
CC=g++
#------------------------------------------------------------------------------
all: $(MYPROGRAM)

$(MYPROGRAM): $(SOURCE)
	$(CC) $(SOURCE) -o$(MYPROGRAM)
clean:
	rm -f $(MYPROGRAM)
