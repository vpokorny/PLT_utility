#Makefile

#Define the C compiler to use
CC = gcc

#Header dir
INC_Utilities = ../../mesh_utilities/
INC_Mesh = ../../mesh_reader
INC_Quadrature = ../../mesh_reader/mesh_reader_quadrature
INC_Points = ../../mesh_reader/mesh_reader_points
INC_Border_line = ../../mesh_reader/mesh_reader_border_line
INC_Line = ../../mesh_reader/mesh_reader_line
INC_Triangle = ../../mesh_reader/mesh_reader_triangle
INC_Quadrangle = ../../mesh_reader/mesh_reader_quadrangle
INC_Functions = ../../mesh_reader/mesh_reader_functions
INC_Intersect = ../
INC_Vertical = ../mesh_intersect_vertical
INC_Horizontal = ../mesh_intersect_horizontal
INC_General = ../mesh_intersect_general

#Source dir
#SRC_DIR = mesh_reader

#Objects dir
#OBJ_DIR = ./ 

#Compiler flags: all warnings + debugger meta-data + inlude of dirs
CFLAGS = -Wall -g

#External libraries:
LIBS = -lm

#Sources

#Objects
OBJS = vertical.o horizontal.o general.o intersect.o

#Dependencies
DEPS =

#Define compilation
.PHONY: default all clean

all: $(OBJS)
	@echo Compiler: $(OBJS) has been compiled.

vertical.o: $(INC_Vertical)/vertical.c $(INC_Utilities)/utilities.h $(INC_Mesh)/mesh.h $(INC_Points)/points.h $(INC_Border_line)/border_line.h $(INC_Line)/line.h $(INC_Triangle)/triangle.h $(INC_Quadrangle)/quadrangle.h $(INC_Functions)/functions.h $(INC_Quadrature)/quadrature.h
	$(CC) $(CFLAGS) -I$(INC_Utilities) -I$(INC_Mesh) -I$(INC_Points) -I$(INC_Border_line) -I$(INC_Line) -I$(INC_Triangle) -I$(INC_Quadrangle) -I$(INC_Functions) -I$(INC_Quadrature) -c $< -o $@
	
horizontal.o: $(INC_Horizontal)/horizontal.c $(INC_Utilities)/utilities.h $(INC_Mesh)/mesh.h $(INC_Points)/points.h $(INC_Border_line)/border_line.h $(INC_Line)/line.h $(INC_Triangle)/triangle.h $(INC_Quadrangle)/quadrangle.h $(INC_Functions)/functions.h $(INC_Quadrature)/quadrature.h
	$(CC) $(CFLAGS) -I$(INC_Utilities) -I$(INC_Mesh) -I$(INC_Points) -I$(INC_Border_line) -I$(INC_Line) -I$(INC_Triangle) -I$(INC_Quadrangle) -I$(INC_Functions) -I$(INC_Quadrature) -c $< -o $@

general.o: $(INC_General)/general.c $(INC_Utilities)/utilities.h $(INC_Mesh)/mesh.h $(INC_Points)/points.h $(INC_Border_line)/border_line.h $(INC_Line)/line.h $(INC_Triangle)/triangle.h $(INC_Quadrangle)/quadrangle.h $(INC_Functions)/functions.h $(INC_Quadrature)/quadrature.h
	$(CC) $(CFLAGS) -I$(INC_Utilities) -I$(INC_Mesh) -I$(INC_Points) -I$(INC_Border_line) -I$(INC_Line) -I$(INC_Triangle) -I$(INC_Quadrangle) -I$(INC_Functions) -I$(INC_Quadrature) -c $< -o $@

intersect.o: $(INC_Intersect)/intersect.c $(INC_Vertical)/vertical.h $(INC_Horizontal)/horizontal.h $(INC_General)/general.h $(INC_Utilities)/utilities.h $(INC_Mesh)/mesh.h $(INC_Points)/points.h $(INC_Border_line)/border_line.h $(INC_Line)/line.h $(INC_Triangle)/triangle.h $(INC_Quadrangle)/quadrangle.h $(INC_Functions)/functions.h $(INC_Quadrature)/quadrature.h
	$(CC) $(CFLAGS) -I$(INC_Vertical) -I$(INC_Horizontal) -I$(INC_General) -I$(INC_Utilities) -I$(INC_Mesh) -I$(INC_Points) -I$(INC_Border_line) -I$(INC_Line) -I$(INC_Triangle) -I$(INC_Quadrangle) -I$(INC_Functions) -I$(INC_Quadrature) -c $< -o $@

clean:
	$(RM) *.o 

