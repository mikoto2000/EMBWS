#include "CHFB.h"

void CHFB_RGB888toRGB565(unsigned char *destimg, unsigned char *srcimg){

	unsigned char r,g,b;

	r = srcimg[0] >> 3;//000rrrrr
	g = srcimg[1] >> 2;//00gggggg
	b = srcimg[2] >> 2;//000bbbbb

	destimg[1] = (r<<3)|(g>>3);//rrrrrggg
	destimg[0] = (g<<5)|b;//gggbbbbb

	if((srcimg[0] != 0xFF && srcimg[1] != 0xFF && srcimg[2] != 0xFF) && (destimg[0] == 0xFF && destimg[1] == 0xFF)){
		destimg[1] = 0xF7;//11110111
		destimg[0] = 0xDE;//11011110
	}
}

void CHFB_convertImage888to565(unsigned char *dest, struct PPM *ppm){
	int i;
	for(i = 0; i < ppm->width * ppm->height * FB_BYTES_PER_PIXEL; i += 2){
		CHFB_RGB888toRGB565(&dest[i], &ppm->img[(int)(i * 1.5)]);
	}
}


unsigned char* CHFB_getFB(){
	FILE *fb_file;
	unsigned char *fb;

		fb_file = fopen("/dev/fb0","r+");
		if (!fb_file) {
			fprintf(stderr,"Can't open /dev/fb0\n");
			exit(1);
		}
		fb = (unsigned char *)mmap(0,
				FB_WIDTH * FB_HEIGHT * FB_BYTES_PER_PIXEL,
				PROT_READ | PROT_WRITE,
				MAP_SHARED,
				fileno(fb_file),
				0);
		if (fb==(unsigned char *)-1) {
			fprintf(stderr,"Can't mmap framebuffer, errno=%d\n",errno);
			exit(1);
		}

		close(fb_file);
	return fb;
}

void CHFB_printImage(unsigned char *base, struct PPM *ppm, int x, int y){
	//baseの先頭アドレスを保存
	unsigned char *startAddress = base;
	unsigned char *endAddress = base+sizeof(unsigned char)*FB_WIDTH*FB_HEIGHT*FB_BYTES_PER_PIXEL;

   //イメージの抽出bg元ファイルはRGB888なので、RGB565に変換
   unsigned char *fg = (unsigned char*)malloc(sizeof(unsigned char) * ppm->width * ppm->height * FB_BYTES_PER_PIXEL);
   CHFB_convertImage888to565(fg, ppm);

	//x,yが画像の中心になるようにする
	x -= ppm->width/2;
	y -= ppm->height/2;

	//左右にはみ出しているピクセルの数
	int lover, rover;
	int newRow = 0;
	lover = -x;
	if(lover < 0){
		lover = 0;
	 }else{
		newRow = +1;
	 }

   int row, col;//行、列
   for(row = 0; row < ppm->height; row++){
      for(col = 0; col < ppm->width; col++){
			int fgIndex, baseIndex;
			fgIndex = row * ppm->width * FB_BYTES_PER_PIXEL + col * FB_BYTES_PER_PIXEL;
			baseIndex = (row + y) * FB_WIDTH * FB_BYTES_PER_PIXEL + (col + x) * FB_BYTES_PER_PIXEL;
		
			//baseバッファの中に収まっているか？
			if(&base[baseIndex] > startAddress && &base[baseIndex] < endAddress){
				//printf("lover:%d base:%x start:%x, end:%x\n", lover, &base[baseIndex],&base[(row + y) * FB_WIDTH * FB_BYTES_PER_PIXEL + newRow] ,&base[(row + y) * FB_WIDTH * FB_BYTES_PER_PIXEL + newRow + FB_WIDTH * FB_BYTES_PER_PIXEL] );
				//プリントしたい行内に収まっているか？
				if(&base[baseIndex] >= &base[(row + y) * FB_WIDTH * FB_BYTES_PER_PIXEL] && &base[baseIndex] < &base[(row + y + newRow) * FB_WIDTH * FB_BYTES_PER_PIXEL + (FB_WIDTH * FB_BYTES_PER_PIXEL)]){
					//透過色(0xFFFF)でなければ上書きする
					if(fg[fgIndex] != 0xFF || fg[fgIndex + 1] != 0xFF){
						base[baseIndex] = fg[fgIndex];
					   base[baseIndex + 1] = fg[fgIndex + 1];
					}
				}
			}	
      }
   }
	free(fg);
}
