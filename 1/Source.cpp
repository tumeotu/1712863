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
	fseek(p, 3L, SEEK_SET);
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
void doc(int n)
{
	int **a = (int **)malloc(2 * sizeof(int));
	*(a ) = (int *)malloc(10 * sizeof(int));
	*(a + 1) = (int *)malloc(5 * sizeof(int));
	for (int i = 0; i < 10; i++)
	{
		printf("nhap:");
		scanf("%d", (*(a)+i));
	}
	for (int i = 0; i < 10; i++)
	{
		printf("nhap:");
		scanf("%d", (*(a)+i));
	}
	for (int i = 0; i < 10; i++)
	{
		printf("%d\t", *(*(a)+i));
	}
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
void docstruct(wchar_t *&arr, FILE *&doc)
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
void main()
{
	sinhvien *ps;
	ps = (sinhvien*)malloc(1* sizeof(sinhvien));
	FILE *fdoc;
	errno_t str;
	str = _wfopen_s(&fdoc, L"C:/Users/TRUONG VAN TU/Desktop/uyendien.csv", L"r, ccs=UTF-8");
	int tell = ftell(fdoc);
	int n = demhoby(fdoc);
	int tell2 = ftell(fdoc);
	fseek(fdoc, -(tell2 - tell), SEEK_CUR);

	*(ps->sothich) = (wchar_t*)malloc(n*sizeof(wchar_t));
	
	for (int i = 0; i < n; i++)
	{
		docstruct(*(ps->sothich + i), fdoc);
	}
}