#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h> //_O_U16TEXT
#include <io.h>    //_setmode()
#include <string.h>
#include <wchar.h>
#define _CRT_SECURE_NO_WARNINGS
struct sinhvien
{
	wchar_t *hoten;
	wchar_t *MSSV;
	wchar_t *nienkhoa;
	wchar_t *khoa;
	wchar_t *ngaysinh;
	wchar_t *mota;
	wchar_t *gmail;
	wchar_t *image;
	wchar_t **sothich;
};
int demhoby(FILE *&p)
{
	wchar_t ch;
	int dem = 1;
	do {
		ch = fgetwc(p);
		if (feof(p))
		{
			break;
		}
		if (ch == ',')
		{
			dem++;
		}
	} while (ch != '\n');
	return dem;
}
int demso(FILE *&p)
{
	wchar_t ch;
	int dem = 0;
	do {
		ch = fgetwc(p);
		if (ch == '\n'){
			dem++;
			return dem;
		}
		if (feof(p))
		{
			dem++;
			break;
		}
		if (ch == '"')
		{
			dem = dem;
		}
		else
		{
			dem++;
		}
	} while (ch != ',');
	return dem;
}
void docstruct(wchar_t *&arr,FILE *&doc)
{
	int lenght;
	wchar_t ch;
	int pos1 = ftell(doc);	 
	lenght = demso(doc);
	int pos2 = ftell(doc);	 	
	arr = (wchar_t*)calloc(lenght + 1, sizeof(wchar_t));
	fseek(doc, -(pos2 - pos1), SEEK_CUR);
	ch = fgetwc(doc);
	if (ch == '"')
	{
		fgetws(arr, lenght, doc);
		arr[wcslen(arr)] = L'\0';
		fseek(doc, 2L, SEEK_CUR);
	}
	else
	{
		fseek(doc, -1L, SEEK_CUR);
		fgetws(arr, lenght, doc);
		//arr[wcslen(arr)] = L'\0';
		fseek(doc, 1L, SEEK_CUR);
	}
	// doc mssv	 	// doc mssv
}
void wdoc(sinhvien *ps, FILE *&doc)
{
	wchar_t ch;
	_setmode(_fileno(stdout), _O_WTEXT); //needed for output
	_setmode(_fileno(stdin), _O_WTEXT);
	// doc ho ten
	docstruct(ps->hoten,doc);
	// doc mssv
	docstruct(ps->MSSV, doc);
	//doc nien khoa
	docstruct(ps->nienkhoa, doc);
	// doc khoa
	docstruct(ps->khoa, doc);
	// doc gmail
	docstruct(ps->gmail, doc);
	// doc image
	docstruct(ps->image, doc);
	// doc ngay thang nam sinh
	docstruct(ps->ngaysinh, doc);
	// doc mo ta
	docstruct(ps->mota, doc);
	// doc so thich
	int tell = ftell(doc);
	int n = demhoby(doc);
	int tell2 = ftell(doc);
	fseek(doc, -(tell2-tell), SEEK_CUR);
	(ps->sothich) = (wchar_t**)malloc(n*sizeof(wchar_t));
	for (int i = 0; i < n; i++)
	{
		if (i == 0)
		{
			docstruct((*(ps->sothich + i)), doc);
			fseek(doc, -1L, SEEK_CUR);
		}
		else
		{
			docstruct(((ps->sothich)), doc);
		}
	
	}
		fseek(doc, 1L, SEEK_CUR);
}
void xuat(sinhvien *ps)
{
	// xuat thong tin
	wprintf(L"\t----THÔNG TIN CÁ NHÂN CỦA BẠN----\n\n");
	wprintf(L"\t%s\n", ps->hoten);
	wprintf(L"\t%s\n", ps->MSSV);
	wprintf(L"\t%s\n", ps->nienkhoa);
	wprintf(L"\t%s\n", ps->khoa);
	wprintf(L"\t%s\n", ps->gmail);
	wprintf(L"\t%s\n", ps->image);
	wprintf(L"\t%s\n", ps->ngaysinh);
	wprintf(L"\t%s\n", ps->mota);
	wprintf(L"\t%s\n\n", *(ps->sothich));
	wprintf(L"\t%s\n\n", *(ps->sothich+1));
	wprintf(L"\t%s\n\n", *(ps->sothich+2));
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
		xuat((SV + i));
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
void thaythe(wchar_t *err, wchar_t *brr, wchar_t *crr)
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
void noichuoi(wchar_t *urr, wchar_t *maso)
{

	wchar_t* htm = L".htm";
	wcscpy(urr, maso);
	wcscat(urr, htm);
	//wprintf(L"%s", urr);
}
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
	while (!feof(D))
	{
		fgetws(arr, 200, D);
		// thay ten
		if (wcsstr(arr, ten) != NULL)
		{
			thaythe(arr, meo->hoten, ten);
		}
		// thay mssv
		if (wcsstr(arr, id) != NULL)
		{
			thaythe(arr, meo->MSSV, id);
		}
		// thay nien khoa
		if (wcsstr(arr, nienkhoa1) != NULL)
		{
			thaythe(arr, meo->nienkhoa, nienkhoa1);
		}
		// thay khoa
		if (wcsstr(arr, khoa1) != NULL)
		{
			thaythe(arr, meo->khoa, khoa1);
		}
		// thay ngay sinh
		if (wcsstr(arr, sinh) != NULL)
		{
			thaythe(arr, meo->ngaysinh, sinh);
		}

		// thay so thich
		/*if (wcsstr(arr, hoby) != NULL)
		{
			thaythe(arr, meo->sothich, hoby);
		}*/
		// thay mo ta
		if (wcsstr(arr, infor) != NULL)
		{
			thaythe(arr, meo->mota, infor);
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
	wchar_t* htm = L".htm";
	for (int i = 0; i < m; i++)
	{

		int size = (wcslen((SV + i)->MSSV) + 4);
		wchar_t *web;
		web = (wchar_t*)malloc(size*sizeof(wchar_t));
		wcscpy(web, (SV + i)->MSSV);
		wcscat(web, htm);
		errno_t str;
		FILE*mo;
		str = _wfopen_s(&mo, web, L"w, ccs=UTF-8");
		if (mo == NULL)
		{
			wprintf(L"k mo dc file");
			return;
		}
		fseek(html, 0L, SEEK_SET);
		write(html, mo, (SV + i));
	}
}
void main()
{
	int n;
	sinhvien *SV;
	FILE* fdoc, *lay, *xuat;
	errno_t err;
	errno_t trr;
	errno_t str;
	err = _wfopen_s(&fdoc, L"C:/Users/TRUONG VAN TU/Desktop/in.csv", L"r, ccs=UTF-8");
	trr = _wfopen_s(&xuat, L"C:/Users/TRUONG VAN TU/Desktop/WEBSITE/1712861.htm", L"w, ccs=UTF-8");
	str = _wfopen_s(&lay, L"C:/Users/TRUONG VAN TU/Desktop/WEBSITE/head.txt", L"r, ccs=UTF-8");
	if (lay == NULL)
	{
		wprintf(L"k mo dc file");
		return;
	}
	n = demsosv(fdoc);
	SV = (sinhvien*)malloc(n* sizeof(sinhvien));
	docdanhsach(fdoc, SV, n);
	//write(lay, xuat, SV);
	xuatdanhsachsinhvien(SV, n);
	//write(lay, xuat, SV);
	//writehtml(SV, lay, fdoc);
	//int kp = demhoby(fdoc);
	//wprintf(L"%d\t", kp);
	fclose(fdoc);
	fclose(xuat);
	fclose(lay);
	free(SV);
}