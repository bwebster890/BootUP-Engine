#include "ImageLoader.h"

#include <GL/glew.h>
#include <libpng/png.h>
#include <cstdlib>

unsigned LoadPNG(std::string path)
{
	png_byte header[8];

	FILE* file = fopen(path.c_str(), "rb");

	fread(header, 1, 8, file);
	png_sig_cmp(header, 0, 8);

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
	png_infop info_ptr = png_create_info_struct(png_ptr);
	png_infop end_info = png_create_info_struct(png_ptr);

	//setjmp(png_jmpbuf(png_ptr));

	png_init_io(png_ptr, file);
	png_set_sig_bytes(png_ptr, 8);
	png_read_info(png_ptr, info_ptr);

	int bit_depth, color_type;
	png_uint_32 temp_width, temp_height;

	png_get_IHDR(png_ptr, info_ptr, &temp_width, &temp_height, &bit_depth, &color_type, 0, 0, 0);
	png_read_update_info(png_ptr, info_ptr);

	int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

	png_byte *image_data = new png_byte[rowbytes * temp_height];
	png_bytep *row_pointers = new png_bytep[temp_height];


	for (int i = 0; i < temp_height; i++)
	{
		row_pointers[temp_height - 1 - i] = (image_data + i * rowbytes);
	}

	png_read_image(png_ptr, row_pointers);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	if (color_type == 2)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, temp_width, temp_height, 0, GL_RGB, GL_UNSIGNED_BYTE, (void*)image_data);
	if (color_type == 6)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, temp_width, temp_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)image_data);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	delete[] image_data;
	delete[] row_pointers;
	fclose(file);

	return texture;
}
