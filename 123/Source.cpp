#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <fcntl.h> //_O_U16TEXT
#include <io.h>    //_setmode()
#include <string.h>
#include <wchar.h>
#define _CRT_SECURE_NO_WARNINGS
struct sinhvien
{
	wchar_t *hoten;
	char *MSSV;
	int *nienkhoa;
	wchar_t *khoa;
	char *ngaysinh;
	wchar_t *mota;
	char *gmail;
	char *image;
	wchar_t *sothich;
};
int demso(FILE *&p)
{
	wchar_t ch;
	int dem = 0;
	do {
		ch = fgetwc(p);
		dem++;
		if (ch == '\n'){
			return dem;
		}
		if (feof(p))
		{
			break;
		}
	} while (ch != ',');
	return dem;
}
void wdoc(sinhvien *ps, FILE *&doc)
{
	int i = 0;
	wchar_t ch;
	_setmode(_fileno(stdout), _O_WTEXT); //needed for output
	_setmode(_fileno(stdin), _O_WTEXT);
// lay dia chi dau dong 
	int line1 = ftell(doc);
	// doc ho ten
	int namelenght;
	int namepos1 = ftell(doc);
	namelenght = demso(doc);
	int namepos2 = ftell(doc);
	ps->hoten = (wchar_t*)calloc(namelenght + 1, sizeof(wchar_t));
	// doc mssv
	fseek(doc, 1L, SEEK_CUR);
	int idlenght;
	int idpos1 = ftell(doc);
	idlenght = demso(doc);
	int idpos2 = ftell(doc);
	ps->MSSV = (char*)calloc(idlenght + 1, sizeof(char));
	//doc nien khoa
	fseek(doc, 1L, SEEK_CUR);
	int nklenght;
	int nkpos1 = ftell(doc);
	nklenght = demso(doc);
	int nkpos2 = ftell(doc);
	ps->nienkhoa = (int*)calloc(2, sizeof(int));
	// doc khoa
	fseek(doc, 1L, SEEK_CUR);
	int khoapos1 = ftell(doc);
	int khoalenght;
	khoalenght = demso(doc);
	int khoapos2 = ftell(doc);
	ps->khoa = (wchar_t*)calloc(khoalenght + 1, sizeof(wchar_t));
	// doc gmail
	fseek(doc, 1L, SEEK_CUR);
	int mailpos1 = ftell(doc);
	int maillenght;
	maillenght = demso(doc);
	int mailpos2 = ftell(doc);
	ps->gmail = (char*)calloc(maillenght + 1, sizeof(char));
	// doc image
	fseek(doc, 1L, SEEK_CUR);
	int imagepos1 = ftell(doc);
	int imagelenght;
	imagelenght = demso(doc);
	int imagepos2 = ftell(doc);
	ps->image = (char*)calloc(imagelenght + 1, sizeof(char));
	// doc ngay thang nam sinh
	fseek(doc, 1L, SEEK_CUR);
	int nslenght;
	int nspos1 = ftell(doc);
	nslenght = demso(doc);
	int nspos2 = ftell(doc);
	ps->ngaysinh = (char*)calloc(nslenght + 1, sizeof(char));
	// doc mo ta
	fseek(doc, 1L, SEEK_CUR);
	int motalenght;
	int mtpos1 = ftell(doc);
	motalenght = demso(doc);
	int mtpos2 = ftell(doc);
	ps->mota = (wchar_t*)calloc(motalenght + 1, sizeof(wchar_t));
	// doc so thich
	fseek(doc, 1L, SEEK_CUR);
	int stlenght;
	int stpos1 = ftell(doc);
	stlenght = demso(doc);
	int stpos2 = ftell(doc);
	ps->sothich = (wchar_t*)calloc(stlenght + 1, sizeof(wchar_t));
	int line2 = ftell(doc);
	fseek(doc, -(line2-line1), SEEK_CUR);
	fwscanf(doc, L"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n],", ps->hoten, ps->MSSV, ps->nienkhoa, ps->khoa, ps->gmail, ps->image, ps->ngaysinh, ps->mota, ps->sothich);
	fseek(doc, 2L, SEEK_CUR);
}
void wxuat(sinhvien *ps)
{
	// xuat thong tin
	wprintf(L"\n\t----THÔNG TIN CÁ NHÂN CỦA BẠN----\n\n");
	wprintf(L"\t%s\n", ps->hoten);
	wprintf(L"\t%s\n", ps->MSSV);
	wprintf(L"\t%s\n", ps->nienkhoa);
	wprintf(L"\t%s\n", ps->khoa);
	wprintf(L"\t%s\n", ps->gmail);
	wprintf(L"\t%s\n", ps->image);
	wprintf(L"\t%s\n", ps->ngaysinh);
	wprintf(L"\t%s\n", ps->mota);
	wprintf(L"\t%s\n\n", ps->sothich);
}
int demsosv(FILE *&fp)
{
	fseek(fp, 0L, SEEK_SET);
	int dem = 0;
	wchar_t ch;
	while (1)
	{
		ch = fgetwc(fp);
		if (ch == '\n')
		{
			dem++;
		}
		if (feof(fp))
		{
			dem++;
			break;
		}
	}
	return dem;
}
void docdanhsach(FILE *&in, sinhvien *&SV, int &n)
{
	n = demsosv(in);
	fseek(in, 3L, SEEK_SET);
	for (int i = 0; i < n; i++)
	{
		wdoc((SV + i), in);
	}
}
void xuatdanhsachsinhvien(sinhvien *&SV, int &n)
{
	for (int i = 0; i < n; i++)
	{
		wxuat((SV + i));
	}
}
int xuli(wchar_t cha[], wchar_t con[])
{
	int cdcha = wcslen(cha), cdcon = wcslen(con), flag = -1;
	for (int i = cdcha - 1; i >= 0; i--)
	{
		for (int j = cdcon - 1; j >= 0; j--)
		{
			if (cha[i] == con[j])
			{
				if (j == 0)
				{
					flag = i;
				}
				i--;
			}
		}
	}
	return flag;
}
void thaythe(wchar_t *err, char *&brr, wchar_t *crr)
{
	wchar_t *drr;
	int arrlenght = wcslen(err);
	int brrlenght = strlen(brr);
	int crrlenght = wcslen(crr);
	int vt = xuli(err, crr);
	int drrlenght = arrlenght - (crrlenght + vt);
	drr = (wchar_t*)malloc((drrlenght)*sizeof(wchar_t));
	wchar_t*idl = (wchar_t*)malloc(brrlenght*sizeof(wchar_t));
	// doi char sang wcha_t
	for (int i = 0; i < brrlenght; i++)
	{
		mbstowcs(idl+i, brr+i, brrlenght );
	}
	for (int i = 0; i < brrlenght; i++)
	{
		wprintf(L"%s", idl + i);
	}
	for (int i = 0; i < drrlenght; i++)
	{
		*(drr + i) = *(err + i + crrlenght + vt);
	}
	for (int i = 0; i < brrlenght; i++)
	{
		*(err + vt + i) = *(idl + i);
	}
	for (int i = vt + brrlenght; i < (vt + brrlenght + drrlenght); i++)
	{
		*(err + i) = *(drr + i - (vt + brrlenght));
	}
	*(err + vt + brrlenght + drrlenght) = '\0';
}
void thay(sinhvien*uyen)
{
	int brrlenght = strlen(uyen->gmail);
	wchar_t*idl = (wchar_t*)malloc(brrlenght*sizeof(wchar_t));
	// doi char sang wcha_t
	for (int i = 0; i < brrlenght; i++)
	{
		mbstowcs(idl,(uyen->MSSV+i) , brrlenght);
	}
	for (int i = 0; i < brrlenght; i++)
	{
		wprintf(L"%s\n", uyen->MSSV);
	}
}
void thaytheunicode(wchar_t *err, wchar_t *brr, wchar_t *crr)
{
	wchar_t *drr;
	int arrlenght = wcslen(err);
	int brrlenght = wcslen(brr);
	int crrlenght = wcslen(crr);
	int vt = xuli(err, crr);
	int drrlenght = arrlenght - (crrlenght + vt);
	drr = (wchar_t*)malloc((drrlenght)*sizeof(wchar_t));
	
	for (int i = 0; i < drrlenght; i++)
	{
		*(drr + i) = *(err + i + crrlenght + vt);
	}

	for (int i = 0; i < brrlenght; i++)
	{
		*(err + vt + i) = *(brr + i);
	}
	for (int i = vt + brrlenght; i < (vt + brrlenght + drrlenght); i++)
	{
		*(err + i) = *(drr + i - (vt + brrlenght));
	}
	*(err + vt + brrlenght + drrlenght) = '\0';
}
//void noichuoi(wchar_t *urr, char *maso)
//{
//	wchar_t* htm = L".htm";
//	wcscpy(urr, idl);
//	wcscat(urr, htm);
//	//wprintf(L"%s", urr);
//}
void write(FILE *&D, FILE *&G, sinhvien *meo)
{
	wchar_t arr[200];
	wchar_t ten[] = L"Truong";
	wchar_t id[] = L"12345678";
	wchar_t khoa1[] = L"CONG";
	wchar_t nienkhoa1[] = L"111";
	wchar_t sinh[] = L"02/01/1998";
	wchar_t hoby[] = L"Am nhac";
	wchar_t infor[] = L"Tôi";
	wchar_t gmail[] = L"t@gmail.com";
	wchar_t image[] = L"tam.png";
	//docnguon(arr, uyen);
	//wprintf(L"%s",ten);
	while (!feof(D))
	{
		fgetws(arr, 200, D);
		// thay ten
		if (wcsstr(arr, ten) != NULL)
		{
			thaytheunicode(arr, meo->hoten, ten);
		}
		// thay mssv
		if (wcsstr(arr, id) != NULL)
		{
			thaythe(arr, meo->MSSV, id);
		}
		// thay nien khoa
		/*if (wcsstr(arr, nienkhoa1) != NULL)
		{
			thaythe(arr, meo->nienkhoa, nienkhoa1);
		}*/
		// thay khoa
		if (wcsstr(arr, khoa1) != NULL)
		{
			thaytheunicode(arr, meo->khoa, khoa1);
		}
		// thay ngay sinh
		if (wcsstr(arr, sinh) != NULL)
		{
			thaythe(arr, meo->ngaysinh, sinh);
		}

		// thay so thich
		if (wcsstr(arr, hoby) != NULL)
		{
			thaytheunicode(arr, meo->sothich, hoby);
		}
		// thay mo ta
		if (wcsstr(arr, infor) != NULL)
		{
			thaytheunicode(arr, meo->mota, infor);
		}
		// thay gmail
		if (wcsstr(arr, gmail) != NULL)
		{
			thaythe(arr, meo->gmail, gmail);
		}
		// thay mo ta
		if (wcsstr(arr, image) != NULL)
		{
			thaythe(arr, meo->image, image);
		}
		fputws(arr, G);
	}
}
void writehtml(sinhvien* SV, FILE *&html, FILE *&ds)
{
	int m = demsosv(ds);
		int size = (strlen((SV)->MSSV) + 4);
		wchar_t *web;
		web = (wchar_t*)malloc(size*sizeof(wchar_t));
		wchar_t* htm = L".htm";
		int n = strlen(SV->MSSV);
		wchar_t*idl = (wchar_t*)malloc(n*sizeof(wchar_t));
		mbstowcs(idl, SV->MSSV, n);
		wcscpy(web, idl);
		wcscat(web, htm);
		errno_t str;
		FILE*mo;
		str = _wfopen_s(&mo, L"1712863.htm", L"w, ccs=UTF-8");
		if (mo == NULL)
		{
			wprintf(L"k mo dc file%s");
			return;
		}
		fseek(html, 0L, SEEK_SET);
		//write(html, mo, (SV));
		thay(SV);
}
void main()
{
	int n;
	sinhvien *SV;
	FILE* fdoc, *lay, *xuat, *mo;
	errno_t err;
	errno_t trr;
	errno_t str;
	err = _wfopen_s(&fdoc, L"C:/Users/TRUONG VAN TU/Desktop/in.csv", L"r, ccs=UTF-8");
	xuat = _wfopen(L"C:/Users/TRUONG VAN TU/Desktop/WEBSITE/1812888.htm", L"w, ccs=UTF-8");
	str = _wfopen_s(&lay, L"C:/Users/TRUONG VAN TU/Desktop/WEBSITE/head.txt", L"r, ccs=UTF-8");
	if (lay == NULL)
	{
		wprintf(L"k mo dc file");
		return;
	}
	n = demsosv(fdoc);
	SV = (sinhvien*)malloc(2* sizeof(sinhvien));
	fseek(fdoc, 3L, SEEK_SET);
	wdoc(SV, fdoc);
	wxuat(SV);
	//docdanhsach(fdoc, SV, n);
	//write(lay, xuat, SV);
	//xuatdanhsachsinhvien(SV, n);
	//write(lay, xuat, SV);
	writehtml(SV, lay, fdoc);
	fclose(fdoc);
	fclose(xuat);
	fclose(lay);
	free(SV);
}