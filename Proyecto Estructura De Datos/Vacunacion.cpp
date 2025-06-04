#include <windows.h>
#include <stdio.h>
#include <wchar.h>
#include"resource.h"
#include <string>
#include<fstream>
#include<oleauto.h>
#include<commctrl.h>
#define MAX_LEN 100
wchar_t UsuarioIn[20], ContraseñaIn[20], UsuarioRe[20], ContraseñaRe[20], cURP[30], rFC[30];
int CreadorId=1;
int num=0;
bool confirmacion = false;
bool iguales = false;
bool conf = false;
char usuariochar[20] = "";
bool imagencargada = false;
OPENFILENAME ofn = {};
WCHAR dirrecion_foto_predeterminada[MAX_PATH] = L"D:\\edgar\\Desktop\\FCFM\\Semestre 4\\Estructura de datos\\PIA\\Imagenes\\ImagenDefecto.bmp";
WCHAR FotoGuardada[MAX_PATH];
HINSTANCE foto;
char ch[MAX_PATH];
char DefChar = ' ';
char busca[100];

// Visual Studio 2019
//De Leon Gonzalez Edgar Eliud 1817164

using namespace std;
// en guardar persona vacuna etc etc ajustaar el id

#define MAX_LOADSTRING 100
SYSTEMTIME date;

struct UYC
{
	char usuario[20];
	char contraseña[20];
	UYC* ant;
	UYC* sig;
}*CUENTAS;
struct Ps
{
	char nombre[30];
	char apellidop[30];
	char apellidom[30];
	char nombrecompleto[100];
	char fechal[30]; 
	char foto[200];
	SYSTEMTIME FECHAS;
	int fechan;
	bool EC;
	bool sexo;
	bool PR;
	char CURP[30];
	char RFC[30];
	char calle[30];
	char colonia[30];
	char cuidad[30];
	char estado[30];
	char telefono[30];
	bool carnet = false;
	Ps* ant;
	Ps* sig;

}*PERSONA;
struct vacuna
{
	char marca[20];
	int numdosis;
	float precio;
	char clave[20];
	char desc[200];
	int Tipo;
	bool S;
	bool M;
	int numvac;
	vacuna* ant;
	vacuna* sig;
	
}*VACUNA;
struct carnet
{
	char CURP[30];
	int dosis;
	int ID;
	char vacuna[30];
	char fechal[30];
	char lotev[30];
	char centro[30];
	SYSTEMTIME fecha;
	SYSTEMTIME fechasig;
	carnet* ant;
	carnet* sig;
}*CARNET;
wstring vacuna1;
vacuna* ClickVacuna = NULL;
Ps* ClickPersona = NULL;
Ps* Bnombres = NULL;
carnet* ClickCarnet = NULL;
// callbacks
BOOL CALLBACK IniciarSecion(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK CrearCuenta(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Busqueda(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK CarnetAlta(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ListaCarnet(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK RegistroPersona(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK RegistroVacuna(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ListaPyV(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ModificarVacuna(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ModificarPersona(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK InfoCarnet(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK InfoPersona(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK InfoVacuna(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK RBusqueda(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam);


UYC* RegistrarUsuario(string usuario, string contraseña/*, string nombre, string app, string apm*/);
void AgregarAListaUYC(UYC* Registro);
void GuardarUsuarios();
void LeerArchivoUsuarios();
int IniciarSeccion(string Uingresado, string Cingresado);
void BorrarMemoria();

vacuna* crearvacuna(string marca, int numdo, float costo, string clave, string desc, int tipe, int numf, bool sem, bool mes);
void AgregarAListaVacunas(vacuna* covi);
void GuardarVacunas();
void LeerArchivoVacuna();
void modificarvacuna(vacuna* cambio, string marca, int numdo, float costo, string clave, string desc, int tipe, int numf, bool sem, bool mes);
void BorrarVacuna(vacuna* selecionado);



Ps* crearpersona(string nombre, string app, string apm, string curp, string rfc, string calle, string colonia, string cuidad, string estado, string telefono, bool ec, bool se, bool re, int fech, string fecha,string foto, SYSTEMTIME xx);
void AgregarPersona(Ps* persona);
void GuardarPersona();
void LeerArchivoPersona();
void modificarpersona(Ps* cambio, string nombre, string app, string apm, string curp, string rfc, string calle, string colonia, string cuidad, string estado, string telefono, bool ec, bool se, bool re, int fech, string fecha, string foto, SYSTEMTIME xx);
void BorrarPersona(Ps* selecionado);

carnet* crearcarnet(string curp, int dosis, string lote, string centro, string vacuna, string fecha,int id, SYSTEMTIME xx, SYSTEMTIME xy);
void AgregarCarnet(carnet* carne);
void GuardarCarnet();
void LeerArchivoCarnet();

void usuariorepetidos(string uno);
void vacunarepetidos(string uno);
void CURP_RFC_Repetidos(string CURP, string rfc);
Ps* buscarcurp(carnet* ingresado);
Ps* buscarcurp(char x[]);
vacuna* buscarvacuna();
void BuscarxNombre(char busca[], HWND ventana);
carnet* buscarcurpcarnet(Ps* buscar);
void buscarbinaria(HWND ventana, int buscar);
bool QuickShortFuncion(HWND ventana, int Cantidad_De_Carnets);
void quicksort(int A[], int izq, int der);
void heapSort(int arr[], int n);
void heapify(int arr[], int n, int i);

std::wstring s2ws(const std::string& s);

BOOL WINAPI WinMain(HINSTANCE hinstance, HINSTANCE Hinstance, LPSTR a, int d) 
{
	CUENTAS = NULL;
	VACUNA = NULL;
	PERSONA = NULL;
	CARNET = NULL;
	LeerArchivoUsuarios();
	LeerArchivoVacuna();
	LeerArchivoPersona();
	LeerArchivoCarnet();
	DialogBox(hinstance, MAKEINTRESOURCE(IDD_IniciarSecion), NULL, (DLGPROC)IniciarSecion);
	GuardarUsuarios(); 
		GuardarVacunas();
		GuardarPersona();
		GuardarCarnet();
	BorrarMemoria();
	return false;
}
BOOL CALLBACK IniciarSecion(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam)
{
	switch (texto)
	{
	case WM_CLOSE:
	{
		DestroyWindow(ventana);
		PostQuitMessage(0);
	}break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:
		{DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_CrearCuenta), NULL, CrearCuenta);
		}break;
		case IDC_BUTTON2:
		{ 
			SendDlgItemMessage(ventana, IDC_EDIT1, WM_GETTEXT, 20, (LPARAM)UsuarioIn);
			SendDlgItemMessage(ventana, IDC_EDIT2, WM_GETTEXT, 20, (LPARAM)ContraseñaIn);
			wstring usr(UsuarioIn);
			wstring cor(ContraseñaIn);
			string susr(usr.begin(), usr.end());
			string scor(cor.begin(), cor.end());
			IniciarSeccion(susr, scor);
			if (confirmacion == true)
			{
				DestroyWindow(ventana);
				DialogBox(NULL,MAKEINTRESOURCE(IDD_Busqueda),NULL,Busqueda);
			}

		}break;
		default:break;
		}
	}break;
	default:break;
	}
	return false;
}
BOOL CALLBACK CrearCuenta(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam)
{
	switch (texto)
	{
	case WM_CLOSE:
	{
		DestroyWindow(ventana);
		//que se pueda crear cuenta y iniciar secion
	}break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_CrearUsuario:
		{
			
			
			TCHAR Trasformer[255];
			GetDlgItemText(ventana, IDC_EDIT1, Trasformer, 255);
			wstring wusin(Trasformer);/* usin USuario Ingresado*/
			GetDlgItemText(ventana, IDC_EDIT2, Trasformer, 255);/* coin COntraseña INgresado y convertirlo a wstring*/
			wstring wcoin(Trasformer);
			string usuario(wusin.begin(), wusin.end());
			string contra(wcoin.begin(), wcoin.end());
			SendDlgItemMessage(ventana, IDC_EDIT1,WM_GETTEXT,20, (LPARAM)UsuarioRe);
			SendDlgItemMessage(ventana, IDC_EDIT2,WM_GETTEXT,20, (LPARAM)ContraseñaRe);
			iguales = false;
			usuariorepetidos(usuario);
			if (iguales==false)
			{
				for (int i = 0; i <= 20; i++)
				{
					if (UsuarioRe[i] == ' ')
					{
						MessageBox(ventana, L"No Se Aceptan Espacios En Blanco", L"ERROR", MB_OK | MB_ICONERROR);
						
						break;
					}
				}
				if (conf != true)
				{
					UYC* Nuevo = RegistrarUsuario(usuario, contra/*, nombre, app, apm*/);
					AgregarAListaUYC(Nuevo);
					
					DestroyWindow(ventana);
					DialogBox(NULL, MAKEINTRESOURCE(IDD_IniciarSecion), NULL, IniciarSecion);
					
				}
			}
			if(iguales == true)
			{
				MessageBox(ventana, L"Ya Exixte un Usuario con ese Nombre ", L"404", MB_OK | MB_ICONERROR);
			}
			//todo esto para poder ingresar nombre y contra en string por que asi es mas facil guardarlo en bin
			//funcion para registrar usuario y agregarlo a la lista
			//crear un if que lea y saber si hay espacios en blancos
			
			

			
		}break;
		case IDC_Cancelar:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_IniciarSecion), NULL, IniciarSecion);
		}break;

		default:break;
		}
	}
	}
	return false;
}
BOOL CALLBACK Busqueda(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam)
{
	switch (texto)
	{
	
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDM_EXIT:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_Busqueda), NULL, Busqueda);
		}break;

		case ID_CARNET_DARDEALTA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_CrearCarnet), NULL, CarnetAlta);
		}break;

		case ID_CARNET_DARDEBAJA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ListaCarnet), NULL, ListaCarnet);
		}break;

		case ID_REGISTRO_NUEVOREGISTRO:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_RegistroPersona), NULL, RegistroPersona);
		}break;

		case ID_REGISTRO_REGISTROVACUNA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_RegistroVacuna), NULL, RegistroVacuna);
		}break;
		case ID_REGISTRO_LISTA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ListaPyV), NULL, ListaPyV);
		}break;

		case ID_SALIR_CERRARPROGRAMA:
		{
			DestroyWindow(ventana);
			PostQuitMessage(0);
		}break;
		case IDOK:
		{TCHAR xd[100];
		GetDlgItemText(ventana, IDC_EDIT1, xd, 100);
		wstring wxd(xd);
		string dx(wxd.begin(), wxd.end());
		strcpy_s(busca, 100, dx.c_str());
		DestroyWindow(ventana);
		DialogBox(NULL, MAKEINTRESOURCE(IDD_RBusqueda), NULL, RBusqueda);
		}break;

		case IDCANCEL:
		{
		}break;
		default:break;
		}
	}break;
	default:break;
	}
	return false;
}
BOOL CALLBACK CarnetAlta(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam)
{
	
	bool Sem = false;
	switch (texto)
	{
		
	case WM_INITDIALOG:
	{
		wstring wvacuna;
		vacuna* indice = VACUNA;
		while (indice != NULL)
		{
			
			
			wvacuna = s2ws(indice->marca);
				int posicion = SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_INSERTSTRING, 0, (LPARAM)wvacuna.c_str());
				SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_SETITEMDATA, posicion, (LPARAM)indice);
				
			indice = indice->sig;
		}
		wstring wpersona;
		Ps * carga = PERSONA;
		while (carga != NULL)
		{
			wpersona = s2ws(carga->nombrecompleto);
			int point = SendMessage(GetDlgItem(ventana, IDC_LIST2), LB_INSERTSTRING, 0, (LPARAM)wpersona.c_str());
			SendMessage(GetDlgItem(ventana, IDC_LIST2), LB_SETITEMDATA, point, (LPARAM)carga);
			carga = carga->sig;
		}
	}break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDM_EXIT:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_Busqueda), NULL, Busqueda);
		}break;

		case ID_CARNET_DARDEALTA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_CrearCarnet), NULL, CarnetAlta);
		}break;

		case ID_CARNET_DARDEBAJA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ListaCarnet), NULL, ListaCarnet);
		}break;

		case ID_REGISTRO_NUEVOREGISTRO:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_RegistroPersona), NULL, RegistroPersona);
		}break;

		case ID_REGISTRO_REGISTROVACUNA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_RegistroVacuna), NULL, RegistroVacuna);
		}break;
		case ID_REGISTRO_LISTA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ListaPyV), NULL, ListaPyV);
		}break;
		case ID_SALIR_CERRARPROGRAMA:
		{
			DestroyWindow(ventana);
			PostQuitMessage(0);
		}break;

		case IDC_LIST1:
		{
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
			{ 
				int selecion = SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_GETCURSEL, 0, 0);
				ClickVacuna = (vacuna*)SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_GETITEMDATA,selecion, 0);
				vacuna1 = s2ws(ClickVacuna->marca);
				num = ClickVacuna->numvac;
					if(ClickVacuna->S = true)
					{
						Sem = true;
					}
				
			}break;
			
			default:
				break;
			}
		}break;
		case IDC_LIST2:
		{
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
			{
				int selecion = SendMessage(GetDlgItem(ventana, IDC_LIST2), LB_GETCURSEL, 0, 0);
				ClickPersona = (Ps*)SendMessage(GetDlgItem(ventana, IDC_LIST2), LB_GETITEMDATA, selecion, 0);
				SetDlgItemText(ventana, IDC_EDIT1, s2ws(ClickPersona->CURP).c_str());


			}break;

			default:
				break;
			}
		}break;
		case IDC_BUTTON1:
		{
			TCHAR tras[255];
			GetDlgItemText(ventana, IDC_EDIT1, tras, 255);
			wstring wcurp(tras);
			string curp(wcurp.begin(), wcurp.end());

			GetDlgItemText(ventana, IDC_EDIT2, tras, 255);
			int dosis = _wtoi(tras);

			GetDlgItemText(ventana, IDC_EDIT4, tras, 255);
			wstring wlote(tras);
			string lote(wlote.begin(), wlote.end());

			GetDlgItemText(ventana, IDC_EDIT5, tras, 255);
			wstring wcentro(tras);
			string centro(wcentro.begin(), wcentro.end());

			GetDlgItemText(ventana, IDC_DATETIMEPICKER1, tras, 255);
			wstring wfecha(tras);
			string fecha(wfecha.begin(), wfecha.end());
			string bakugan(vacuna1.begin(), vacuna1.end());
			SYSTEMTIME date2;
			DateTime_GetSystemtime(GetDlgItem(ventana, IDC_DATETIMEPICKER1), &date);
			DateTime_GetSystemtime(GetDlgItem(ventana, IDC_DATETIMEPICKER1), &date2);

			if (Sem = true)
			{
				date2.wDay = date2.wDay + (7 * num);
			}
			else
			{
				date2.wMonth = date.wMonth + num;
			}

			carnet* NEW = crearcarnet(curp, dosis, lote, centro, bakugan, fecha,CreadorId,date,date2);
			AgregarCarnet(NEW);
			MessageBox(ventana, L"Succes", L"Se A Creado Carnet", MB_OK);
			ClickPersona->carnet = true;
			ClickPersona = NULL;
			ClickVacuna = NULL;
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_Busqueda), NULL, Busqueda);

		}break;
		default:break;
		}
	}break;
	default:break;
	}
	return false;
}
BOOL CALLBACK ListaCarnet(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam)
{
	switch (texto)
	{
	case WM_INITDIALOG:
	{
		SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_RESETCONTENT, 0, 0);
		wstring wnombre;
		carnet* indice = CARNET;
			while (indice != NULL)
			{
				wnombre = s2ws(indice->CURP);
				int point = SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_INSERTSTRING, 0, (LPARAM)wnombre.c_str());
				SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_SETITEMDATA, point, (LPARAM)indice);
				indice = indice->sig;
			}
	}break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDM_EXIT:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_Busqueda), NULL, Busqueda);
		}break;

		case ID_CARNET_DARDEALTA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_CrearCarnet), NULL, CarnetAlta);
		}break;

		case ID_CARNET_DARDEBAJA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ListaCarnet), NULL, ListaCarnet);
		}break;

		case ID_REGISTRO_NUEVOREGISTRO:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_RegistroPersona), NULL, RegistroPersona);
		}break;

		case ID_REGISTRO_REGISTROVACUNA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_RegistroVacuna), NULL, RegistroVacuna);
		}break;
		case ID_REGISTRO_LISTA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ListaPyV), NULL, ListaPyV);
		}break;
		case ID_SALIR_CERRARPROGRAMA:
		{
			DestroyWindow(ventana);
			PostQuitMessage(0);
		}break;
		case IDOK:
		{
			if (ClickCarnet != NULL)
			{
			 DestroyWindow(ventana);
			 DialogBox(NULL, MAKEINTRESOURCE(IDD_InfoCarnet), NULL, InfoCarnet);
			}
		}break;
		
		case IDC_BUTTON1:
		{
			int num = 0;
			carnet* indice = CARNET;
			while (indice != NULL)
			{
				num++;
				indice = indice->sig;
			}
			indice = NULL;
			QuickShortFuncion(ventana, num);

		}break;
		case IDC_BUTTON2:
		{
			SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_RESETCONTENT, 0, 0);
			int cadena[MAX_LOADSTRING];
			int num = 0;
			carnet* indice = CARNET;
			while (indice != NULL)
			{
				cadena[num]=indice->ID;
				num++;
				indice = indice->sig;
			}
			indice = NULL;
			carnet* lista = CARNET;
			Ps* nombre = NULL;
			string nombrecompleto;
			
			
			heapSort(cadena, num);
			bool Imprimio = false;
			int id = 0;
			int cant_personas = 0;
			nombre = PERSONA;
			while (nombre != NULL)
			{
				cant_personas++;
				nombre = nombre->sig;
			}

			lista = CARNET;
			num--;

			for (int i = num; i >= 0 ; i = i)
			{

				id = cadena[i];
				char palabra = cadena[i];
				nombre = buscarcurp(lista);

				char busqueda_nombre[30];
				wstring wnombre = s2ws(nombre->nombrecompleto);
				string snombre(wnombre.begin(), wnombre.end());
				strcpy_s(busqueda_nombre, snombre.c_str());

				if (id == lista->ID)
				{

					int point = SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_INSERTSTRING, 0, (LPARAM)wnombre.c_str());
					SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_SETITEMDATA, point, (LPARAM)lista);

					Imprimio = true;
					i--;

				}
				lista = lista->sig;
				if (Imprimio == true)
				{
					lista = CARNET;
					Imprimio = false;
				}
			}

		}break;
		case IDC_LIST1:
		{
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
			{
				int selecion = SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_GETCURSEL, 0, 0);
				ClickCarnet = (carnet*)SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_GETITEMDATA, selecion, 0);
			}break;

			default:
				break;
			}
		}break;

		default:break;
		}
	}break;
	default:break;
	}
	return false;
}
BOOL CALLBACK RegistroPersona(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam)
{
	switch (texto)
	{
	case WM_INITDIALOG:
	{HBITMAP imagen;
	
	if (imagencargada==false)
	{
		imagen = (HBITMAP)LoadImage(foto, dirrecion_foto_predeterminada, IMAGE_BITMAP, 125, 125, LR_LOADFROMFILE | LR_DEFAULTSIZE);
		SendDlgItemMessage(ventana, IDC_FOTO, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
	}
	else
	{
		imagen = (HBITMAP)LoadImage(foto, FotoGuardada, IMAGE_BITMAP, 125, 125, LR_LOADFROMFILE | LR_DEFAULTSIZE);
		SendDlgItemMessage(ventana, IDC_FOTO, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
		
	}


	}break;
	case WM_COMMAND:
	{
	/*case WM_CLOSE:
	{
		DestroyWindow(ventana);
		PostQuitMessage(0);
	}break;*/
		switch (LOWORD(wParam))
		{
		case IDM_EXIT:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_Busqueda), NULL, Busqueda);
		}break;

		case ID_CARNET_DARDEALTA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_CrearCarnet), NULL, CarnetAlta);
		}break;

		case ID_CARNET_DARDEBAJA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ListaCarnet), NULL, ListaCarnet);
		}break;

		case ID_REGISTRO_NUEVOREGISTRO:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_RegistroPersona), NULL, RegistroPersona);
		}break;

		case ID_REGISTRO_REGISTROVACUNA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_RegistroVacuna), NULL, RegistroVacuna);
		}break;
		case ID_REGISTRO_LISTA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ListaPyV), NULL, ListaPyV);
		}break;
		case ID_SALIR_CERRARPROGRAMA:
		{
			DestroyWindow(ventana);
			PostQuitMessage(0);
		}break;

		case IDC_BUTTON3:
		{ 
			conf = false;
			TCHAR tras[255];
			GetDlgItemText(ventana, IDC_EDIT2, tras, 255);
			wstring wnombre(tras);
			string nombre(wnombre.begin(),wnombre.end());

			GetDlgItemText(ventana, IDC_EDIT3, tras, 255);
			wstring wapp(tras);
			string app(wapp.begin(), wapp.end());

			GetDlgItemText(ventana, IDC_EDIT4, tras, 255);
			wstring wapm(tras);
			string apm(wapm.begin(),wapm.end());

			GetDlgItemText(ventana, IDC_EDIT5, tras, 255);
			wstring wcurp(tras);
			string curp(wcurp.begin(), wcurp.end());

			GetDlgItemText(ventana, IDC_EDIT6, tras, 255);
			wstring wrfc(tras);
			string rfc(wrfc.begin(), wrfc.end());

			GetDlgItemText(ventana, IDC_EDIT7, tras, 255);
			wstring wcalle(tras);
			string calle(wcalle.begin(), wcalle.end());

			GetDlgItemText(ventana, IDC_EDIT8, tras, 255);
			wstring wcolonia(tras);
			string colonia(wcolonia.begin(), wcolonia.end());

			GetDlgItemText(ventana, IDC_EDIT9, tras, 255);
			wstring wcuidad(tras);
			string cuidad(wcuidad.begin(), wcuidad.end());

			GetDlgItemText(ventana, IDC_EDIT10, tras, 255);
			wstring westado(tras);
			string estado(westado.begin(), westado.end());

			GetDlgItemText(ventana, IDC_EDIT11, tras, 255);
			wstring wtel(tras);
			string tel(wtel.begin(), wtel.end());
			bool EC ;
			string FotoaGuardar;
			if (imagencargada == true)
			{
				WideCharToMultiByte(CP_ACP, 0, FotoGuardada, -1, ch, MAX_PATH, &DefChar, NULL);
				FotoaGuardar=ch;

			}
			else
			{
				WideCharToMultiByte(CP_ACP, 0, dirrecion_foto_predeterminada, -1, ch, MAX_PATH, &DefChar, NULL);
				FotoaGuardar = ch;
			}
			
			if (IsDlgButtonChecked(ventana, IDC_RADIO1) == BST_CHECKED)
			{
			   EC = true;
			}
			else 
			{
				if (IsDlgButtonChecked(ventana, IDC_RADIO2) == BST_CHECKED)
				{
					EC = false;
				}
			}

			bool SE;
			if (IsDlgButtonChecked(ventana, IDC_RADIO3) == BST_CHECKED)
			{
				SE = true;
			}
			else
			{
				if (IsDlgButtonChecked(ventana, IDC_RADIO4) == BST_CHECKED)
				{
					SE = false;
				}
			}

			bool RE;
			if (IsDlgButtonChecked(ventana, IDC_RADIO5) == BST_CHECKED)
			{
				RE = true;
			}
			else
			{
				if (IsDlgButtonChecked(ventana, IDC_RADIO6) == BST_CHECKED)
				{
					RE = false;
				}
			}
			//falta fecha
			GetDlgItemText(ventana, IDC_DATETIMEPICKER1, tras, 255);
			wstring wfecha1(tras);
			string fecha1(wfecha1.begin(), wfecha1.end());

			double f2;
			DateTime_GetSystemtime(GetDlgItem(ventana, IDC_DATETIMEPICKER1), &date);
			SystemTimeToVariantTime(&date, &f2);
			date.wHour = 0;
			date.wMilliseconds = 0;
			date.wMinute = 0;
			date.wSecond = 0;
			
			SendDlgItemMessage(ventana, IDC_EDIT5,WM_GETTEXT, 30, (LPARAM)cURP);
			SendDlgItemMessage(ventana, IDC_EDIT6, WM_GETTEXT, 30, (LPARAM)rFC);



			if (nombre != "")
			{
				if (app!= "")
				{
					if (apm != "")
					{
						if (curp!="")
						{
							if (rfc != "")
							{
								if (calle != "")
								{
									if (colonia != "")
									{
										if (cuidad != "")
										{
											if (estado != "")
											{//if(EC!=NULL)
												iguales = false;
												CURP_RFC_Repetidos(curp, rfc);
												if (iguales == false)
												{
													for (int i = 0; i <= 20; i++)
													{
														if (cURP[i] == ' ')
														{
															MessageBox(ventana, L"No Se Aceptan Espacios En Blancos en CURP", L"ERROR", MB_OK | MB_ICONERROR);
															conf = true;
															break;
														}
														if (rFC[i] == ' ')
														{
															MessageBox(ventana, L"No Se Aceptan Espacios En Blancos en RFC", L"ERROR", MB_OK | MB_ICONERROR);
															conf = true;
														}
													}
													if (conf != true)
													{
														Ps* nuevo = crearpersona(nombre, app, apm, curp, rfc, calle, colonia, cuidad, estado, tel, EC, SE, RE, f2, fecha1,FotoaGuardar,date);

														

														AgregarPersona(nuevo);

														MessageBox(ventana, L"Se Registro a la persona", L"complete", MB_OK);
														imagencargada = false;
														DestroyWindow(ventana);
														DialogBox(NULL, MAKEINTRESOURCE(IDD_Busqueda), NULL, Busqueda);
													}
												}
												else
												{
													MessageBox(ventana, L"CURP o RFC ya Registrados", L"ERROR", MB_OK);
												}
											}
											else
											{
												MessageBox(ventana, L"Falta LLenar estado ", L"404", MB_OK|MB_ICONERROR);
												break;
											}
										}
										else
										{
											MessageBox(ventana, L"Falta LLenar Cuidad ", L"404", MB_OK | MB_ICONERROR);
											break;
										}
									}
									else
									{
										MessageBox(ventana, L"Falta LLenar Colonia ", L"404", MB_OK | MB_ICONERROR);
										break;
									}
								}
								else
								{
									MessageBox(ventana, L"Falta LLenar Calle ", L"404", MB_OK | MB_ICONERROR);
									break;
								}
							}
							else
							{
								MessageBox(ventana, L"Falta LLenar RFC", L"404", MB_OK | MB_ICONERROR);
								break;
							}
						}
						else
						{
							MessageBox(ventana, L"Falta LLenar CURP ", L"404", MB_OK | MB_ICONERROR);
							break;
						}
					}
					else
					{
						MessageBox(ventana, L"Falta LLenar Apellido Materno ", L"404", MB_OK | MB_ICONERROR);
						break;
					}
				}
				else
				{
					MessageBox(ventana, L"Falta LLenar Apellido Paterno", L"404", MB_OK | MB_ICONERROR);
					break;
				}
			}
			else
			{
				MessageBox(ventana, L"Falta LLenar Nombres", L"404", MB_OK | MB_ICONERROR);
				break;
			}

			
			
		
		
		
		
		}break;
		case IDC_BUTTON4:
		{
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = ventana;
			ofn.lpstrFile = FotoGuardada;
			ofn.lpstrFilter = L"Imagenes Bit Map\0*.bmp*";
			ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
			ofn.lpstrFile[0] = NULL;
			ofn.nMaxFile = sizeof(FotoGuardada);
			ofn.nFilterIndex = 0;
			if (GetOpenFileName(&ofn) == TRUE)
			{
				SetDlgItemText(ventana, IDC_FOTO, FotoGuardada);
			}
			imagencargada = true;
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_RegistroPersona), NULL, RegistroPersona);
		}break;
		default:break;
		}
	}break;
	default:break;
	}
	return false;
}
BOOL CALLBACK RegistroVacuna(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam)
{
	switch (texto)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDM_EXIT:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_Busqueda), NULL, Busqueda);
		}break;

		case ID_CARNET_DARDEALTA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_CrearCarnet), NULL, CarnetAlta);
		}break;

		case ID_CARNET_DARDEBAJA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ListaCarnet), NULL, ListaCarnet);
		}break;

		case ID_REGISTRO_NUEVOREGISTRO:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_RegistroPersona), NULL, RegistroPersona);
		}break;

		case ID_REGISTRO_REGISTROVACUNA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_RegistroVacuna), NULL, RegistroVacuna);
		}break;
		case ID_REGISTRO_LISTA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ListaPyV), NULL, ListaPyV);
		}break;
		case ID_SALIR_CERRARPROGRAMA:
		{
			DestroyWindow(ventana);
			PostQuitMessage(0);
		}break;

		case IDC_BUTTON3:
		{
			iguales = false;
			TCHAR trans[255];
			GetDlgItemText(ventana, IDC_EDIT1, trans, 255);
			wstring wmarca(trans);
			string marca(wmarca.begin(), wmarca.end());

			GetDlgItemText(ventana, IDC_EDIT2, trans, 255);
			int nudosis = _wtoi(trans);

			GetDlgItemText(ventana, IDC_EDIT3, trans, 255);
			float precio = _wtoi(trans);
			
			GetDlgItemText(ventana, IDC_EDIT6, trans, 255);
			int numdia=_wtoi(trans);

			GetDlgItemText(ventana, IDC_EDIT4, trans, 255);
			wstring wclave = (trans);
			string clave(wclave.begin(), wclave.end());

			GetDlgItemText(ventana, IDC_EDIT5, trans, 255);
			wstring wdesc(trans);
			string desc(wdesc.begin(), wdesc.end());



			bool s = false;
			bool m = false;

			int tip = 0;
			if (IsDlgButtonChecked(ventana, IDC_RADIO1) == BST_CHECKED)
			{
				tip = 1;
			}
			if (IsDlgButtonChecked(ventana, IDC_RADIO2) == BST_CHECKED)
			{
				tip = 2;
			}
			if (IsDlgButtonChecked(ventana, IDC_RADIO3) == BST_CHECKED)
			{
				tip = 3;
			}
			if (IsDlgButtonChecked(ventana, IDC_RADIO4) == BST_CHECKED)
			{
				tip = 4;
			}
			if (IsDlgButtonChecked(ventana, IDC_RADIO5) == BST_CHECKED)
			{
				s = true;
			}
			if (IsDlgButtonChecked(ventana, IDC_RADIO6) == BST_CHECKED)
			{
				m = true;
			}
			if (marca != "")
			{
				if (precio > 0)
				{
					if (clave != "")
					{
						if (desc != "")
						{
							vacunarepetidos(marca);

							if (iguales != true)
							{
								vacuna* nuevo = crearvacuna(marca, nudosis, precio, clave, desc, tip,numdia,s,m);
								AgregarAListaVacunas(nuevo);
								MessageBox(ventana, L"Exito", L"se Registro Vacuna", MB_OK);
								DestroyWindow(ventana);
								DialogBox(NULL, MAKEINTRESOURCE(IDD_Busqueda), NULL, Busqueda);
							}
							else
							{
								MessageBox(ventana, L"Ya Existe Una Vacuna de la misma Marca", L"ERROR", MB_OK | MB_ICONERROR);
							}
						}
						else
						{
							MessageBox(ventana, L"Falta LLenar Clave ", L"404", MB_OK | MB_ICONERROR);
							break;
						}
					}
					else
					{
						MessageBox(ventana, L"Falta LLenar Describcion ", L"404", MB_OK | MB_ICONERROR);
						break;
					}
					
				}
				else
				{
					MessageBox(ventana, L"Precio debe ser mayor a 0 ", L"404", MB_OK | MB_ICONERROR);
					break;
				}
			}
			else
			{
				MessageBox(ventana, L"Falta LLenar Marca ", L"404", MB_OK | MB_ICONERROR);
				break;
			}
		
				
			
		}break;
		
		default:break;
	}
	}break;
	default:break;
	}
	return false;
	}
BOOL CALLBACK ListaPyV(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam)
{
	switch (texto)
	{
	case WM_INITDIALOG:
		{
		ClickPersona = NULL;
		ClickVacuna = NULL;
		SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_RESETCONTENT, 0, 0);
		SendMessage(GetDlgItem(ventana, IDC_LIST2), LB_RESETCONTENT, 0, 0);

		wstring wvacuna;
		vacuna* vacunalista = VACUNA;
		while (vacunalista != NULL)
		{
			wvacuna = s2ws(vacunalista->marca);
			int point = SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_INSERTSTRING, 0, (LPARAM)wvacuna.c_str());
			SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_SETITEMDATA, point, (LPARAM)vacunalista);
			vacunalista = vacunalista->sig;
		}
		wstring wpersona;
		Ps* personalista = PERSONA;
		while (personalista != NULL)
		{
			wpersona = s2ws(personalista->nombrecompleto);
			
			int point1 = SendMessage(GetDlgItem(ventana, IDC_LIST2), LB_INSERTSTRING, 0, (LPARAM)wpersona.c_str());
			SendMessage(GetDlgItem(ventana, IDC_LIST2), LB_SETITEMDATA, point1, (LPARAM)personalista);
			personalista = personalista->sig;
		}



		}break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDM_EXIT:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_Busqueda), NULL, Busqueda);
		}break;

		case ID_CARNET_DARDEALTA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_CrearCarnet), NULL, CarnetAlta);
		}break;

		case ID_CARNET_DARDEBAJA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ListaCarnet), NULL, ListaCarnet);
		}break;

		case ID_REGISTRO_NUEVOREGISTRO:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_RegistroPersona), NULL, RegistroPersona);
		}break;

		case ID_REGISTRO_REGISTROVACUNA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_RegistroVacuna), NULL, RegistroVacuna);
		}break;
		case ID_REGISTRO_LISTA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ListaPyV), NULL, ListaPyV);
		}break;
		case ID_SALIR_CERRARPROGRAMA:
		{
			DestroyWindow(ventana);
			PostQuitMessage(0);
		}break;

		case IDC_LIST1:
		{
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
			{
				int Selec = SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_GETCURSEL, 0, 0);
				ClickVacuna = (vacuna*)SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_GETITEMDATA, Selec, 0);
				ClickPersona = NULL;
				//abrir callback
			}break;
			default:break;
			}
		}break;
		case IDC_LIST2:
		{
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
			{
				int Selec = SendMessage(GetDlgItem(ventana, IDC_LIST2), LB_GETCURSEL, 0, 0);
				ClickPersona = (Ps*)SendMessage(GetDlgItem(ventana, IDC_LIST2), LB_GETITEMDATA, Selec, 0);
				ClickVacuna = NULL;
				//abrir callback
			}break;
			default:break;
			}
		}break;
		case IDOK:
		{
			
			if (ClickPersona != NULL)
			{
				DestroyWindow(ventana);
				DialogBox(NULL, MAKEINTRESOURCE(IDD_ModificarPersonas), NULL, ModificarPersona);
			}
			if (ClickVacuna != NULL)
			{
				DestroyWindow(ventana);
				DialogBox(NULL, MAKEINTRESOURCE(IDD_ModificarVacuna), NULL, ModificarVacuna);
			}
		}break;
		case IDCANCEL:
		{
			if (ClickPersona != NULL)
			{
				BorrarPersona(ClickPersona);
				DestroyWindow(ventana);
				DialogBox(NULL, MAKEINTRESOURCE(IDD_ListaPyV), NULL, ListaPyV);
			}
			if (ClickVacuna != NULL)
			{
				BorrarVacuna(ClickVacuna);
				DestroyWindow(ventana);
				DialogBox(NULL, MAKEINTRESOURCE(IDD_ListaPyV), NULL, ListaPyV);
			
			}
		}break;

		default:break;
		}
	}break;
	default:break;
	}

	return false;
}
BOOL CALLBACK ModificarVacuna(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam)
{
	switch (texto)
	{
	case WM_INITDIALOG:
	{
		SetDlgItemText(ventana, IDC_EDIT1, s2ws(ClickVacuna->marca).c_str());
		SetDlgItemText(ventana, IDC_EDIT2, s2ws(to_string(ClickVacuna->numdosis)).c_str());
		SetDlgItemText(ventana, IDC_EDIT3, s2ws(to_string(ClickVacuna->precio)).c_str());
		SetDlgItemText(ventana, IDC_EDIT4, s2ws(ClickVacuna->clave).c_str());
		SetDlgItemText(ventana, IDC_EDIT5, s2ws(ClickVacuna->desc).c_str());
		SetDlgItemText(ventana, IDC_EDIT6, s2ws(to_string(ClickVacuna->numvac)).c_str());
		if (ClickVacuna->Tipo == 1)
		{
			CheckDlgButton(ventana, IDC_RADIO1, BST_CHECKED);
		}
		if (ClickVacuna->Tipo == 2)
		{
			CheckDlgButton(ventana, IDC_RADIO2, BST_CHECKED);
		}
		if (ClickVacuna->Tipo == 3)
		{
			CheckDlgButton(ventana, IDC_RADIO3, BST_CHECKED);
		}
		if (ClickVacuna->Tipo == 4)
		{
			CheckDlgButton(ventana, IDC_RADIO4, BST_CHECKED);
		}
		if (ClickVacuna->S=true)
		{
			CheckDlgButton(ventana, IDC_RADIO5, BST_CHECKED);
		}
		if (ClickVacuna->M = true)
		{
			CheckDlgButton(ventana, IDC_RADIO6, BST_CHECKED);
		}

	}break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDM_EXIT:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_Busqueda), NULL, Busqueda);
		}break;

		case ID_CARNET_DARDEALTA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_CrearCarnet), NULL, CarnetAlta);
		}break;

		case ID_CARNET_DARDEBAJA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ListaCarnet), NULL, ListaCarnet);
		}break;

		case ID_REGISTRO_NUEVOREGISTRO:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_RegistroPersona), NULL, RegistroPersona);
		}break;

		case ID_REGISTRO_REGISTROVACUNA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_RegistroVacuna), NULL, RegistroVacuna);
		}break;
		case ID_REGISTRO_LISTA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ListaPyV), NULL, ListaPyV);
		}break;

		case ID_SALIR_CERRARPROGRAMA:
		{
			DestroyWindow(ventana);
			PostQuitMessage(0);
		}break;
		case IDC_BUTTON3:
		{
			iguales = false;
			TCHAR trans[255];
			GetDlgItemText(ventana, IDC_EDIT1, trans, 255);
			wstring wmarca(trans);
			string marca(wmarca.begin(), wmarca.end());

			GetDlgItemText(ventana, IDC_EDIT2, trans, 255);
			int nudosis = _wtoi(trans);

			GetDlgItemText(ventana, IDC_EDIT3, trans, 255);
			float precio = _wtoi(trans);


			GetDlgItemText(ventana, IDC_EDIT4, trans, 255);
			wstring wclave = (trans);
			string clave(wclave.begin(), wclave.end());

			GetDlgItemText(ventana, IDC_EDIT5, trans, 255);
			wstring wdesc(trans);
			string desc(wdesc.begin(), wdesc.end());

			GetDlgItemText(ventana, IDC_EDIT6, trans, 255);
			int numdia = _wtoi(trans);
			bool s = false;
			bool m = false;

			int tip = 0;
			if (IsDlgButtonChecked(ventana, IDC_RADIO1) == BST_CHECKED)
			{
				tip = 1;
			}
			if (IsDlgButtonChecked(ventana, IDC_RADIO2) == BST_CHECKED)
			{
				tip = 2;
			}
			if (IsDlgButtonChecked(ventana, IDC_RADIO3) == BST_CHECKED)
			{
				tip = 3;
			}
			if (IsDlgButtonChecked(ventana, IDC_RADIO4) == BST_CHECKED)
			{
				tip = 4;
			}
			if (IsDlgButtonChecked(ventana, IDC_RADIO5) == BST_CHECKED)
			{
				s = true;
			}
			if (IsDlgButtonChecked(ventana, IDC_RADIO6) == BST_CHECKED)
			{
				m = true;
			}

			

			if (marca != "")
			{
				if (precio > 0)
				{
					if (clave != "")
					{
						if (desc != "")
						{
							modificarvacuna(ClickVacuna, marca, nudosis, precio, clave, desc, tip, numdia, s, m);
							MessageBox(ventana, L"Se realizo los cambios en vacuna", L"etc", MB_OK);
							DestroyWindow(ventana);
							DialogBox(NULL, MAKEINTRESOURCE(IDD_ListaPyV), NULL, ListaPyV);

						}
						else
						{
							MessageBox(ventana, L"Falta LLenar Clave ", L"404", MB_OK | MB_ICONERROR);
							break;
						}
					}
					else
					{
						MessageBox(ventana, L"Falta LLenar Describcion ", L"404", MB_OK | MB_ICONERROR);
						break;
					}

				}
				else
				{
					MessageBox(ventana, L"Precio debe ser mayor a 0 ", L"404", MB_OK | MB_ICONERROR);
					break;
				}
			}
			else
			{
				MessageBox(ventana, L"Falta LLenar Marca ", L"404", MB_OK | MB_ICONERROR);
				break;
			}
				
			
				
			

		//funcion para cambiar
		}break;


		default:break;
		}
	}break;
	default:break;
	}
	return false;
}
BOOL CALLBACK ModificarPersona(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam)
{
	switch (texto)
	{
	case WM_INITDIALOG:
	{HBITMAP imagen;
	if (imagencargada == false)
	{
		wstring wdirrecion = s2ws(ClickPersona->foto);
		wchar_t* PTR = _wcsdup(wdirrecion.c_str());
		imagen = (HBITMAP)LoadImage(foto, PTR, IMAGE_BITMAP, 125, 125, LR_LOADFROMFILE | LR_DEFAULTSIZE);
		SendDlgItemMessage(ventana, IDC_FOTO, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
	}
	else
	{
		imagen = (HBITMAP)LoadImage(foto, FotoGuardada, IMAGE_BITMAP, 125, 125, LR_LOADFROMFILE | LR_DEFAULTSIZE);
		SendDlgItemMessage(ventana, IDC_FOTO, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
	}
	//SetDlgItemText(ventana, IDC_EDIT1, s2ws(ClickVacuna->marca).c_str());
	//SetDlgItemText(ventana, IDC_EDIT2, s2ws(to_string(ClickVacuna->numdosis)).c_str());
	SetDlgItemText(ventana, IDC_EDIT2, s2ws(ClickPersona->nombre).c_str());
	SetDlgItemText(ventana, IDC_EDIT3, s2ws(ClickPersona->apellidop).c_str());
	SetDlgItemText(ventana, IDC_EDIT4, s2ws(ClickPersona->apellidom).c_str());
	DateTime_SetSystemtime(GetDlgItem(ventana, IDC_DATETIMEPICKER1), GDT_VALID,&ClickPersona->FECHAS);
	SetDlgItemText(ventana, IDC_EDIT5, s2ws(ClickPersona->CURP).c_str());
	SetDlgItemText(ventana, IDC_EDIT6, s2ws(ClickPersona->RFC).c_str());
	SetDlgItemText(ventana, IDC_EDIT7, s2ws(ClickPersona->calle).c_str());
	SetDlgItemText(ventana, IDC_EDIT8, s2ws(ClickPersona->colonia).c_str());
	SetDlgItemText(ventana, IDC_EDIT9, s2ws(ClickPersona->cuidad).c_str());
	SetDlgItemText(ventana, IDC_EDIT10, s2ws(ClickPersona->estado).c_str());
	SetDlgItemText(ventana, IDC_EDIT11, s2ws(ClickPersona->telefono).c_str());
	if (ClickPersona->EC == true)
	{
		CheckDlgButton(ventana, IDC_RADIO1, BST_CHECKED);
	}
	else
	{
		CheckDlgButton(ventana, IDC_RADIO2, BST_CHECKED);
	}
	if (ClickPersona->sexo == true)
	{
		CheckDlgButton(ventana, IDC_RADIO3, BST_CHECKED);
	}
	else
	{
		CheckDlgButton(ventana, IDC_RADIO4, BST_CHECKED);
	}
	if (ClickPersona->PR == true)
	{
		CheckDlgButton(ventana, IDC_RADIO5, BST_CHECKED);
	}
	else
	{
		CheckDlgButton(ventana, IDC_RADIO6, BST_CHECKED);
	}
	}break;
	case WM_COMMAND:
	{
	/*case WM_CLOSE:
	{
		DestroyWindow(ventana);
		PostQuitMessage(0);
	}break;*/
		switch (LOWORD(wParam))
		{
		case IDM_EXIT:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_Busqueda), NULL, Busqueda);
		}break;

		case ID_CARNET_DARDEALTA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_CrearCarnet), NULL, CarnetAlta);
		}break;

		case ID_CARNET_DARDEBAJA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ListaCarnet), NULL, ListaCarnet);
		}break;

		case ID_REGISTRO_NUEVOREGISTRO:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_RegistroPersona), NULL, RegistroPersona);
		}break;

		case ID_REGISTRO_REGISTROVACUNA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_RegistroVacuna), NULL, RegistroVacuna);
		}break;
		case ID_REGISTRO_LISTA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ListaPyV), NULL, ListaPyV);
		}break;
		case ID_SALIR_CERRARPROGRAMA:
		{
			DestroyWindow(ventana);
			PostQuitMessage(0);
		}break;

		case IDC_BUTTON3:
		{ 
			conf = false;
			TCHAR tras[255];
			GetDlgItemText(ventana, IDC_EDIT2, tras, 255);
			wstring wnombre(tras);
			string nombre(wnombre.begin(),wnombre.end());

			GetDlgItemText(ventana, IDC_EDIT3, tras, 255);
			wstring wapp(tras);
			string app(wapp.begin(), wapp.end());

			GetDlgItemText(ventana, IDC_EDIT4, tras, 255);
			wstring wapm(tras);
			string apm(wapm.begin(),wapm.end());

			GetDlgItemText(ventana, IDC_EDIT5, tras, 255);
			wstring wcurp(tras);
			string curp(wcurp.begin(), wcurp.end());

			GetDlgItemText(ventana, IDC_EDIT6, tras, 255);
			wstring wrfc(tras);
			string rfc(wrfc.begin(), wrfc.end());

			GetDlgItemText(ventana, IDC_EDIT7, tras, 255);
			wstring wcalle(tras);
			string calle(wcalle.begin(), wcalle.end());

			GetDlgItemText(ventana, IDC_EDIT8, tras, 255);
			wstring wcolonia(tras);
			string colonia(wcolonia.begin(), wcolonia.end());

			GetDlgItemText(ventana, IDC_EDIT9, tras, 255);
			wstring wcuidad(tras);
			string cuidad(wcuidad.begin(), wcuidad.end());

			GetDlgItemText(ventana, IDC_EDIT10, tras, 255);
			wstring westado(tras);
			string estado(westado.begin(), westado.end());

			GetDlgItemText(ventana, IDC_EDIT11, tras, 255);
			wstring wtel(tras);
			string tel(wtel.begin(), wtel.end());
			bool EC ;
			string FotoSelecionada;
			if (imagencargada == true)
			{
				WideCharToMultiByte(CP_ACP, 0, FotoGuardada, -1, ch, MAX_PATH, &DefChar, NULL);
				FotoSelecionada = ch;

			}
			
			
		
			
			if (IsDlgButtonChecked(ventana, IDC_RADIO1) == BST_CHECKED)
			{
			   EC = true;
			}
			else 
			{
				if (IsDlgButtonChecked(ventana, IDC_RADIO2) == BST_CHECKED)
				{
					EC = false;
				}
			}

			bool SE;
			if (IsDlgButtonChecked(ventana, IDC_RADIO3) == BST_CHECKED)
			{
				SE = true;
			}
			else
			{
				if (IsDlgButtonChecked(ventana, IDC_RADIO4) == BST_CHECKED)
				{
					SE = false;
				}
			}

			bool RE;
			if (IsDlgButtonChecked(ventana, IDC_RADIO5) == BST_CHECKED)
			{
				RE = true;
			}
			else
			{
				if (IsDlgButtonChecked(ventana, IDC_RADIO6) == BST_CHECKED)
				{
					RE = false;
				}
			}
			//falta fecha
			GetDlgItemText(ventana, IDC_DATETIMEPICKER1, tras, 255);
			wstring wfecha1(tras);
			string fecha1(wfecha1.begin(), wfecha1.end());

			double f2;
			DateTime_GetSystemtime(GetDlgItem(ventana, IDC_DATETIMEPICKER1), &date);
			SystemTimeToVariantTime(&date, &f2);
			date.wHour = 0;
			date.wMilliseconds = 0;
			date.wMinute = 0;
			date.wSecond = 0;
			int fecha2 = (int)f2;
			
			SendDlgItemMessage(ventana, IDC_EDIT5,WM_GETTEXT, 30, (LPARAM)cURP);
			SendDlgItemMessage(ventana, IDC_EDIT6, WM_GETTEXT, 30, (LPARAM)rFC);

			CURP_RFC_Repetidos(curp, rfc);
			modificarpersona(ClickPersona, nombre, app, apm, curp, rfc, calle, colonia, cuidad, estado, tel, EC, SE, RE, fecha2, fecha1, FotoSelecionada, date);
			MessageBox(NULL, L"Se Modifico Registro de Persona", L"Cambio De Registro", MB_OK);
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ListaPyV), NULL, ListaPyV);
		
		
		
		}break;
		case IDC_BUTTON4:
		{
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = ventana;
			ofn.lpstrFile = FotoGuardada;
			ofn.lpstrFilter = L"Imagenes Bit Map\0*.bmp*";
			ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
			ofn.lpstrFile[0] = NULL;
			ofn.nMaxFile = sizeof(FotoGuardada);
			ofn.nFilterIndex = 0;
			if (GetOpenFileName(&ofn) == TRUE)
			{
				SetDlgItemText(ventana, IDC_FOTO, FotoGuardada);
			}
			imagencargada = true;
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ModificarPersonas), NULL, ModificarPersona);
		}break;
		default:break;
		}
	}break;
	default:break;
	}
	return false;
}
BOOL CALLBACK InfoCarnet(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam)
{
	switch (texto)
	{
	case WM_INITDIALOG:
	{
		
		//SetDlgItemText(ventana, IDC_EDIT1, s2ws(ClickVacuna->marca).c_str());
		//SetDlgItemText(ventana, IDC_EDIT2, s2ws(to_string(ClickVacuna->numdosis)).c_str());
		SetDlgItemText(ventana, IDC_EDIT1, s2ws(ClickCarnet->CURP).c_str());
		SetDlgItemText(ventana, IDC_EDIT2, s2ws(to_string(ClickCarnet->dosis)).c_str());

		SetDlgItemText(ventana, IDC_EDIT4, s2ws(ClickCarnet->lotev).c_str());
		SetDlgItemText(ventana, IDC_EDIT5, s2ws(ClickCarnet->centro).c_str());
		date = ClickCarnet->fechasig;
		DateTime_SetSystemtime(GetDlgItem(ventana, IDC_DATETIMEPICKER1), GDT_VALID, &date);
		
	}break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDM_EXIT:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_Busqueda), NULL, Busqueda);
		}break;

		case ID_CARNET_DARDEALTA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_CrearCarnet), NULL, CarnetAlta);
		}break;

		case ID_CARNET_DARDEBAJA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ListaCarnet), NULL, ListaCarnet);
		}break;

		case ID_REGISTRO_NUEVOREGISTRO:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_RegistroPersona), NULL, RegistroPersona);
		}break;

		case ID_REGISTRO_REGISTROVACUNA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_RegistroVacuna), NULL, RegistroVacuna);
		}break;
		case ID_REGISTRO_LISTA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ListaPyV), NULL, ListaPyV);
		}break;

		case ID_SALIR_CERRARPROGRAMA:
		{
			DestroyWindow(ventana);
			PostQuitMessage(0);
		}break;
		case IDC_BUTTON1:
		{
			ClickPersona = buscarcurp(ClickCarnet);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_InfoPersonas), NULL, InfoPersona);
			ClickPersona = NULL;

		}break;
		case IDC_BUTTON3:
		{
			ClickVacuna = buscarvacuna();
			DialogBox(NULL, MAKEINTRESOURCE(IDD_InfoVacuna), NULL, InfoVacuna);
			ClickVacuna = NULL;
		}break;

		default:break;
		}
	}break;
	default:break;
	}
	return false;
}
BOOL CALLBACK InfoPersona(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam)
{
	switch (texto)
	{
	case WM_INITDIALOG:
	{HBITMAP imagen;

	wstring wdirrecion = s2ws(ClickPersona->foto);
	wchar_t* PTR = _wcsdup(wdirrecion.c_str());
	imagen = (HBITMAP)LoadImage(foto, PTR, IMAGE_BITMAP, 125, 125, LR_LOADFROMFILE | LR_DEFAULTSIZE);
	SendDlgItemMessage(ventana, IDC_FOTO, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);

	
	SetDlgItemText(ventana, IDC_EDIT2, s2ws(ClickPersona->nombre).c_str());
	SetDlgItemText(ventana, IDC_EDIT3, s2ws(ClickPersona->apellidop).c_str());
	SetDlgItemText(ventana, IDC_EDIT4, s2ws(ClickPersona->apellidom).c_str());
	DateTime_SetSystemtime(GetDlgItem(ventana, IDC_DATETIMEPICKER1), GDT_VALID, &ClickPersona->FECHAS);
	SetDlgItemText(ventana, IDC_EDIT5, s2ws(ClickPersona->CURP).c_str());
	SetDlgItemText(ventana, IDC_EDIT6, s2ws(ClickPersona->RFC).c_str());
	SetDlgItemText(ventana, IDC_EDIT7, s2ws(ClickPersona->calle).c_str());
	SetDlgItemText(ventana, IDC_EDIT8, s2ws(ClickPersona->colonia).c_str());
	SetDlgItemText(ventana, IDC_EDIT9, s2ws(ClickPersona->cuidad).c_str());
	SetDlgItemText(ventana, IDC_EDIT10, s2ws(ClickPersona->estado).c_str());
	SetDlgItemText(ventana, IDC_EDIT11, s2ws(ClickPersona->telefono).c_str());
	if (ClickPersona->EC == true)
	{
		CheckDlgButton(ventana, IDC_RADIO1, BST_CHECKED);
	}
	else
	{
		CheckDlgButton(ventana, IDC_RADIO2, BST_CHECKED);
	}
	if (ClickPersona->sexo == true)
	{
		CheckDlgButton(ventana, IDC_RADIO3, BST_CHECKED);
	}
	else
	{
		CheckDlgButton(ventana, IDC_RADIO4, BST_CHECKED);
	}
	if (ClickPersona->PR == true)
	{
		CheckDlgButton(ventana, IDC_RADIO5, BST_CHECKED);
	}
	else
	{
		CheckDlgButton(ventana, IDC_RADIO6, BST_CHECKED);
	}
	}break;
	case WM_CLOSE:
	{
		DestroyWindow(ventana);
	}break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{

		default:break;
		}
	}break;
	default:break;
	}
	return false;

}
BOOL CALLBACK InfoVacuna(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam)
{
	switch (texto)
	{
	case WM_INITDIALOG:
	{
		SetDlgItemText(ventana, IDC_EDIT1, s2ws(ClickVacuna->marca).c_str());
		SetDlgItemText(ventana, IDC_EDIT2, s2ws(to_string(ClickVacuna->numdosis)).c_str());
		SetDlgItemText(ventana, IDC_EDIT3, s2ws(to_string(ClickVacuna->precio)).c_str());
		SetDlgItemText(ventana, IDC_EDIT4, s2ws(ClickVacuna->clave).c_str());
		SetDlgItemText(ventana, IDC_EDIT5, s2ws(ClickVacuna->desc).c_str());
		SetDlgItemText(ventana, IDC_EDIT6, s2ws(to_string(ClickVacuna->numvac)).c_str());
		if (ClickVacuna->Tipo == 1)
		{
			CheckDlgButton(ventana, IDC_RADIO1, BST_CHECKED);
		}
		if (ClickVacuna->Tipo == 2)
		{
			CheckDlgButton(ventana, IDC_RADIO2, BST_CHECKED);
		}
		if (ClickVacuna->Tipo == 3)
		{
			CheckDlgButton(ventana, IDC_RADIO3, BST_CHECKED);
		}
		if (ClickVacuna->Tipo == 4)
		{
			CheckDlgButton(ventana, IDC_RADIO4, BST_CHECKED);
		}
		if (ClickVacuna->S = true)
		{
			CheckDlgButton(ventana, IDC_RADIO5, BST_CHECKED);
		}
		if (ClickVacuna->M = true)
		{
			CheckDlgButton(ventana, IDC_RADIO6, BST_CHECKED);
		}

	}break;
	case WM_CLOSE:
	{
		DestroyWindow(ventana);
	}break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{

		default:break;
		}
	}break;
	default:break;
	}
	return false;
}
BOOL CALLBACK RBusqueda(HWND ventana, UINT texto, WPARAM wParam, LPARAM lParam)
{
	switch (texto)
{
	case WM_INITDIALOG:
	{
		TCHAR xd[100];


		if (busca[0] == '1' || busca[0] == '2' || busca[0] == '3' || busca[0] == '4' || busca[0] == '5' || busca[0] == '6' || busca[0] == '7' || busca[0] == '8' || busca[0] == '9')
		{
			//funcion buscar en binario
			int numero = atoi(busca);
			buscarbinaria(ventana, numero);
		}
		else
		{
			BuscarxNombre(busca, ventana);
		}
			
	}break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDM_EXIT:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_Busqueda), NULL, Busqueda);
		}break;

		case ID_CARNET_DARDEALTA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_CrearCarnet), NULL, CarnetAlta);
		}break;

		case ID_CARNET_DARDEBAJA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ListaCarnet), NULL, ListaCarnet);
		}break;

		case ID_REGISTRO_NUEVOREGISTRO:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_RegistroPersona), NULL, RegistroPersona);
		}break;

		case ID_REGISTRO_REGISTROVACUNA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_RegistroVacuna), NULL, RegistroVacuna);
		}break;
		case ID_REGISTRO_LISTA:
		{
			DestroyWindow(ventana);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ListaPyV), NULL, ListaPyV);
		}break;
		case ID_SALIR_CERRARPROGRAMA:
		{
			DestroyWindow(ventana);
			PostQuitMessage(0);
		}break;
		case IDC_LIST1:
		{
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
			{
				int selecion = SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_GETCURSEL, 0, 0);
				ClickPersona = (Ps*)SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_GETITEMDATA, selecion, 0);
				ClickCarnet= buscarcurpcarnet(ClickPersona);
				DestroyWindow(ventana);
				DialogBox(NULL, MAKEINTRESOURCE(IDD_InfoCarnet), NULL, InfoCarnet);
			}break;

			default:
				break;
			}
		}break;

		default:break;
		}

	}
}
	
	return false;
}

//funciones
UYC* RegistrarUsuario(string usuario, string contraseña/*, string nombre, string app, string apm*/)
{
	if (usuario!= "")
	{
		if (contraseña != "")
		{
			UYC* Nuevo = new UYC;
			strcpy_s(Nuevo->usuario, 20, usuario.c_str());
			strcpy_s(Nuevo->contraseña, 20, contraseña.c_str());
			Nuevo->ant = NULL;
			Nuevo->sig = NULL;
			MessageBox(NULL, L"Info", L"Se A Creado Su Cuenta", MB_OK | MB_ICONINFORMATION);
			return Nuevo;
		}
	}
	else
	{
		MessageBox(NULL, L"No Se Acepta Espacios en Blanco", L"ERROR", MB_OK | MB_ICONERROR);
	}
	return NULL;
}
void AgregarAListaUYC(UYC* Registro)
{
	if (CUENTAS == NULL)
	{
		CUENTAS = Registro;
	}
	else
	{
		UYC* Lista = CUENTAS;
		while (Lista->sig != NULL)
		{
			Lista = Lista->sig;
		}
		Lista->sig = Registro;
		Registro->ant = Lista;

	}
}
void GuardarUsuarios()
{
	ofstream Guardado;
	Guardado.open("D:\\edgar\\Desktop\\FCFM\\Semestre 4\\Estructura de datos\\PIA\\Datos Guardados\\Usuarios.bin", ios::binary | ios::trunc);
	if (Guardado.is_open())
	{
		UYC* lista = CUENTAS;
		while (lista != NULL)
		{
			Guardado.write((char*)lista, sizeof(UYC));
			lista = lista->sig;
		}
		Guardado.close();
	}
}
void LeerArchivoUsuarios()
{
	ifstream Leer;
	Leer.open("D:\\edgar\\Desktop\\FCFM\\Semestre 4\\Estructura de datos\\PIA\\Datos Guardados\\Usuarios.bin", ios::binary | ios::in);
	if (Leer.is_open())
	{
		Leer.seekg(0, Leer.end);
		int archivo = Leer.tellg();
		Leer.seekg(0, Leer.beg);
		int tamaño = 0;
		while (tamaño < archivo)
		{
			UYC* info = new UYC;
			Leer.read(reinterpret_cast<char*>(info), sizeof(UYC));
			info->sig = NULL;
			info->ant = NULL;
			
			AgregarAListaUYC(info);
			tamaño = tamaño + sizeof(UYC);
		}
		Leer.close();
	}
}

vacuna* crearvacuna(string marca,int numdo, float costo,string clave,string desc, int tipe,int numf,bool sem,bool mes)
{
	vacuna* crear = new vacuna;
	strcpy_s(crear->marca, 20, marca.c_str());
	crear->numdosis = numdo;
	crear->precio = costo;
	strcpy_s(crear->clave, 20, clave.c_str());
	strcpy_s(crear->desc, 200, desc.c_str());
	crear->Tipo = tipe;
	crear->numvac = numf;
	crear->S = sem;
	crear->M = mes;
	crear->ant = NULL;
	crear->sig = NULL;
	return crear;
}
void AgregarAListaVacunas(vacuna* covi)
{
	if (VACUNA == NULL)
	{
		VACUNA = covi;
	}
	else
	{
		vacuna* lista = VACUNA;
		while (lista->sig != NULL)
		{
			lista = lista->sig;
		}
		lista->sig = covi;
		covi->ant = lista;
	}
}
void GuardarVacunas()
{
	ofstream Guardado;
	Guardado.open("D:\\edgar\\Desktop\\FCFM\\Semestre 4\\Estructura de datos\\PIA\\Datos Guardados\\Vacunas.bin", ios::binary | ios::trunc);
	if (Guardado.is_open())
	{
		vacuna* lista = VACUNA;
		while (lista != NULL)
		{
			Guardado.write((char*)lista, sizeof(vacuna));
			lista = lista->sig;
		}
		Guardado.close();
	}
}
void LeerArchivoVacuna()
{
	ifstream Leer;
	Leer.open("D:\\edgar\\Desktop\\FCFM\\Semestre 4\\Estructura de datos\\PIA\\Datos Guardados\\Vacunas.bin", ios::binary | ios::in);
	if (Leer.is_open())
	{
		Leer.seekg(0, Leer.end);
		int archivo = Leer.tellg();
		Leer.seekg(0, Leer.beg);
		int tamaño = 0;
		while (tamaño < archivo)
		{
			vacuna* info = new vacuna;
			Leer.read(reinterpret_cast<char*>(info), sizeof(vacuna));
			info->sig = NULL;
			info->ant = NULL;
			
			AgregarAListaVacunas(info);
			tamaño = tamaño + sizeof(vacuna);
		}
		Leer.close();
	}
}
void modificarvacuna(vacuna* cambio, string marca, int numdo, float costo, string clave, string desc, int tipe, int numf, bool sem, bool mes)
{
	if (marca != "")
	{
		strcpy_s(cambio->marca, 20, marca.c_str());
	}
	if (numdo != 0)
	{
		cambio->numdosis = numdo;
	}
	if (costo != 0)
	{
		cambio->precio = costo;
	}
	if (clave != "")
	{
		strcpy_s(cambio->clave, 20, clave.c_str());
	}
	if (desc != "")
	{
		strcpy_s(cambio->desc, 200, desc.c_str());
	}
	if (tipe != 0)
	{
		cambio->Tipo = tipe;
	}
	cambio->numvac = numf;
	cambio->S = sem;
	cambio->M = mes;
}

Ps* crearpersona(string nombre,string app, string apm, string curp, string rfc, string calle, string colonia, string cuidad,string estado,string telefono,bool ec, bool se, bool re,int fech,string fecha,string foto,SYSTEMTIME xx)
{
	Ps* crear = new Ps;
	strcpy_s(crear->nombre,30,nombre.c_str());
	strcpy_s(crear->apellidop,30,app.c_str());
	strcpy_s(crear->apellidom, 30, apm.c_str());
	strcpy_s(crear->CURP, 30, curp.c_str());
	strcpy_s(crear->RFC, 30, rfc.c_str());
	strcpy_s(crear->calle, 30, calle.c_str());
	strcpy_s(crear->colonia, 30, colonia.c_str());
	strcpy_s(crear->cuidad, 30, cuidad.c_str());
	strcpy_s(crear->estado, 30, estado.c_str());

	
	strcpy_s(crear->nombrecompleto, crear->nombre);
	strcat_s(crear->nombrecompleto, " ");
	strcat_s(crear->nombrecompleto, crear->apellidop);
	strcat_s(crear->nombrecompleto, " ");
	strcat_s(crear->nombrecompleto, crear->apellidom);

	strcpy_s(crear->telefono, 30, telefono.c_str());
	crear->EC = ec;
	crear->sexo = se;
	crear->PR = re;
	crear->fechan = fech;
	strcpy_s(crear->fechal, 30, fecha.c_str());
	strcpy_s(crear->foto, 200, foto.c_str());
	
	crear->FECHAS = xx;
	
	crear->sig = NULL;
	crear->ant = NULL;
	return crear;

}
void AgregarPersona(Ps* persona)
{
	if (PERSONA == NULL)
	{
		PERSONA = persona;
	}
	else
	{
		Ps* lista = PERSONA;
		while (lista->sig != NULL)
		{
			lista = lista->sig;
		}
		lista->sig = persona;
		persona->ant = lista;
	}
}
void GuardarPersona()
{
	ofstream Guardado;
	Guardado.open("D:\\edgar\\Desktop\\FCFM\\Semestre 4\\Estructura de datos\\PIA\\Datos Guardados\\Persona.bin", ios::binary | ios::trunc);
	if (Guardado.is_open())
	{
		Ps* lista = PERSONA;
		while (lista != NULL)
		{
			Guardado.write((char*)lista, sizeof(Ps));
			lista = lista->sig;
		}
		Guardado.close();
	}
}
void LeerArchivoPersona()
{
	ifstream Leer;
	Leer.open("D:\\edgar\\Desktop\\FCFM\\Semestre 4\\Estructura de datos\\PIA\\Datos Guardados\\Persona.bin", ios::binary | ios::in);
	if (Leer.is_open())
	{
		Leer.seekg(0, Leer.end);
		int archivo = Leer.tellg();
		Leer.seekg(0, Leer.beg);
		int tamaño = 0;
		while (tamaño < archivo)
		{
			Ps* info = new Ps;
			Leer.read(reinterpret_cast<char*>(info), sizeof(Ps));
			info->sig = NULL;
			info->ant = NULL;
			
			AgregarPersona(info);
			tamaño = tamaño + sizeof(Ps);
		}
		Leer.close();
	}
}
void modificarpersona(Ps* cambio, string nombre, string app, string apm, string curp, string rfc, string calle, string colonia, string cuidad, string estado, string telefono, bool ec, bool se, bool re, int fech, string fecha, string foto, SYSTEMTIME xx)
{
	if (nombre != "")
	{
		strcpy_s(cambio->nombre, 30, nombre.c_str());
	}
	if (app != "")
	{
		strcpy_s(cambio->apellidop, 30, app.c_str());
	}
	if (apm != "")
	{
		strcpy_s(cambio->apellidom, 30, apm.c_str());
	}
	if (curp != "")
	{
		strcpy_s(cambio->CURP, 30, curp.c_str());
	}
	if (rfc != "")
	{
		strcpy_s(cambio->RFC, 30, rfc.c_str());
	}
	if (calle != "")
	{
		strcpy_s(cambio->calle, 30, calle.c_str());
	}
    if (colonia != "")
	{
		strcpy_s(cambio->colonia, 30, colonia.c_str());
	}
	if (cuidad != "")
	{
		strcpy_s(cambio->cuidad, 30, cuidad.c_str());
	}
	if (estado != "")
	{ 
		strcpy_s(cambio->estado, 30, estado.c_str());
	}
	if (telefono != "")
	{
		strcpy_s(cambio->telefono, 30, telefono.c_str());
	}
	cambio->EC = ec;
	cambio->sexo = se;
	cambio->PR = re;
	if (fech != 0)
	{
		cambio->fechan = fech;
	}
	if (fecha != "")
	{ 
		strcpy_s(cambio->fechal, 30, fecha.c_str());
	}
	if (foto != "")
	{
		strcpy_s(cambio->foto, 30, foto.c_str());
	}		
	cambio->FECHAS = xx;

	strcpy_s(cambio->nombrecompleto, cambio->nombre);
	strcat_s(cambio->nombrecompleto, " ");
	strcat_s(cambio->nombrecompleto, cambio->apellidop);
	strcat_s(cambio->nombrecompleto, " ");
	strcat_s(cambio->nombrecompleto, cambio->apellidom);

	
}

carnet* crearcarnet(string curp, int dosis, string lote, string centro, string vacuna, string fecha,int id,SYSTEMTIME xx,SYSTEMTIME xy)
{
	carnet* Crear = new carnet;
	strcpy_s(Crear->CURP, 30, curp.c_str());
	Crear->dosis = dosis;
	strcpy_s(Crear->lotev, 30, lote.c_str());
	strcpy_s(Crear->centro, 30, centro.c_str());
	strcpy_s(Crear->vacuna, 30, vacuna.c_str());
	strcpy_s(Crear->fechal, 30, fecha.c_str());
	Crear->ID = id;
	Crear->fecha = xx;
	Crear->fechasig = xy;
	Crear->ant = NULL;
	Crear->sig = NULL;
	CreadorId++;
	return Crear;
}
void AgregarCarnet(carnet* carne)
{
	if (CARNET == NULL)
	{
		CARNET = carne;
	}
	else
	{
		carnet* lista = CARNET;
		while (lista->sig != NULL)
		{
			lista = lista->sig;
		}
		lista->sig = carne;
		carne->ant = lista;
	}
}
void GuardarCarnet()
{
	ofstream Guardado;
	Guardado.open("D:\\edgar\\Desktop\\FCFM\\Semestre 4\\Estructura de datos\\PIA\\Datos Guardados\\Carnet.bin", ios::binary | ios::trunc);
	if (Guardado.is_open())
	{
		carnet* lista = CARNET;
		while (lista != NULL)
		{
			Guardado.write((char*)lista, sizeof(carnet));
			lista = lista->sig;
		}
		Guardado.close();
	}
}
void LeerArchivoCarnet()
{
	ifstream Leer;
	Leer.open("D:\\edgar\\Desktop\\FCFM\\Semestre 4\\Estructura de datos\\PIA\\Datos Guardados\\Carnet.bin", ios::binary | ios::in);
	if (Leer.is_open())
	{
		Leer.seekg(0, Leer.end);
		int archivo = Leer.tellg();
		Leer.seekg(0, Leer.beg);
		int tamaño = 0;
		while (tamaño < archivo)
		{
			carnet* info = new carnet;
			Leer.read(reinterpret_cast<char*>(info), sizeof(carnet));
			info->sig = NULL;
			info->ant = NULL;
			CreadorId++;
			AgregarCarnet(info);
			tamaño = tamaño + sizeof(carnet);
		}
		Leer.close();
	}
}

int IniciarSeccion(string Uingresado, string Cingresado)
{
	UYC* Lista = CUENTAS;
	if (CUENTAS == NULL)
	{
		return NULL;
	}
	while (Lista != NULL)
	{
		if (_strcmpi(Lista->usuario, Uingresado.c_str()) == 0 && _strcmpi(Lista->contraseña, Cingresado.c_str()) == 0)
		{
			confirmacion = true;
			MessageBox(NULL, L"Exito", L"Bienvenido", MB_OK | MB_ICONINFORMATION);
			break;
		}
		Lista = Lista->sig;
	}
	if (confirmacion != true)
	{
		MessageBox(NULL, L"El Usuairo o contraseña No son los correctos", L"ERROR", MB_OK | MB_ICONERROR);
	}
	return confirmacion;
}
void BorrarMemoria()
{
	UYC* lista = CUENTAS;
	while (lista != NULL)
	{
		UYC* borrar = lista;
		lista = lista->sig;
		delete borrar;
	}
	CUENTAS = NULL;
	vacuna* list = VACUNA;
	while (list != NULL)
	{
		vacuna* borra = list;
		list = list->sig;
		delete borra;
	}
	VACUNA = NULL;
	Ps* mementos = PERSONA;
	while (mementos != NULL)
	{
		Ps* borra = mementos;
		mementos = mementos->sig;
		delete borra;
	}
	PERSONA = NULL;
	carnet* garnet = CARNET;
	while (garnet != NULL)
	{
		carnet* borra = garnet;
		garnet = garnet->sig;
		delete borra;
	}
	CARNET = NULL;
}
void usuariorepetidos(string uno)
{
	wstring wcomparacion;
	UYC* Lista = CUENTAS;
	while (Lista != NULL)
	{
		wcomparacion = s2ws(Lista->usuario);
		string comparacion(wcomparacion.begin(), wcomparacion.end());
		if (comparacion.compare(uno) == 0)
		{
			iguales = true;

			break;
		}
		Lista = Lista->sig;
	}
	
}
void vacunarepetidos(string uno)
{
	wstring wcomparacion;
	vacuna* Lista = VACUNA;
	while (Lista != NULL)
	{
		wcomparacion = s2ws(Lista->marca);
		string comparacion(wcomparacion.begin(), wcomparacion.end());
		if (comparacion.compare(uno) == 0)
		{
			iguales = true;

			break;
		}
		Lista = Lista->sig;
	}

}
void CURP_RFC_Repetidos(string CURP,string rfc)
{
	wstring wcomparacionCurp;
	wstring wcomparacionRfc;
	Ps* Lista = PERSONA;
	while (Lista != NULL)
	{
		wcomparacionCurp = s2ws(Lista->CURP);
		string comparacionCurp(wcomparacionCurp.begin(), wcomparacionCurp.end());
		if (comparacionCurp.compare(CURP) == 0)
		{
			iguales = true;

			break;
		}
		wcomparacionRfc = s2ws(Lista->RFC);
		string comparacionRfc(wcomparacionRfc.begin(), wcomparacionRfc.end());
		if (comparacionRfc.compare(rfc)==0)
		{
			iguales = true;
			break;
		}
		Lista = Lista->sig;
	}

}
void BorrarVacuna(vacuna* selecionado)
{
	if (VACUNA == NULL)
	{
		return;
	}
	
	if (selecionado != NULL)
	{
		vacuna* Anterior = selecionado->ant;
		vacuna* Siguiente = selecionado->sig;
		if (Anterior == NULL && Siguiente != NULL)
		{
			Siguiente->ant = NULL;
			delete selecionado;
			VACUNA = Siguiente;
		}
		if (Siguiente == NULL && Anterior != NULL)
		{
			Anterior->sig = NULL;
			delete selecionado;
		}
		if (Anterior != NULL && Siguiente != NULL)
		{
			Anterior->sig = Siguiente;
			Siguiente->ant = Anterior;
			delete selecionado;
		}
		if (Anterior == NULL && Siguiente == NULL)
		{
			if (Anterior == NULL && Siguiente == NULL)
			{
				delete selecionado;
			}
			VACUNA = NULL;
		}
		MessageBox(NULL, L"Se Elimino La Vacuna Del Registro", L"Cambios De Registro", MB_OK |MB_ICONINFORMATION);
		ClickVacuna = NULL;
	}
	
}
void BorrarPersona(Ps* selecionado)
{
	if (PERSONA == NULL)
	{
		return;
	}

	if (selecionado != NULL)
	{
		Ps* Anterior = selecionado->ant;
		Ps* Siguiente = selecionado->sig;
		if (Anterior == NULL && Siguiente != NULL)
		{
			Siguiente->ant = NULL;
			delete selecionado;
			PERSONA = Siguiente;
		}
		if (Siguiente == NULL && Anterior != NULL)
		{
			Anterior->sig = NULL;
			delete selecionado;
		}
		if (Anterior != NULL && Siguiente != NULL)
		{
			Anterior->sig = Siguiente;
			Siguiente->ant = Anterior;
			delete selecionado;
		}
		if (Anterior == NULL && Siguiente == NULL)
		{
			if (Anterior == NULL && Siguiente == NULL)
			{
				delete selecionado;
			}
			PERSONA = NULL;
		}
		MessageBox(NULL, L"Se Elimino La Persona Del Registro", L"Cambios De Registro", MB_OK | MB_ICONINFORMATION);
		ClickPersona = NULL;
	}

}
Ps* buscarcurp(carnet*ingresado)
{
	Ps*buscar= PERSONA;
	while (buscar != NULL)
	{
		{
			if (strcmp(ingresado->CURP, buscar->CURP) == 0)
			{
				return buscar;
			}
		}
		buscar = buscar->sig;
	}
}
Ps* buscarcurp(char x[])
{
	Ps* buscar = PERSONA;
	while (buscar != NULL)
	{
		{
			if (strcmp(x, buscar->CURP) == 0)
			{
				return buscar;
			}
		}
		buscar = buscar->sig;
	}
}
carnet* buscarcurpcarnet(Ps*buscar)
{
	carnet* check = CARNET;
	while (check != NULL)
	{
		if (strcmp(check->CURP, buscar->CURP) == 0)
		{
			return check;
		}
		check = check->sig;
	}
}
vacuna* buscarvacuna()
{
	vacuna* buscar = VACUNA;
	while (buscar != NULL)
	{
		if (strcmp(ClickCarnet->CURP, buscar->marca) == 0)
		{
			return buscar;
		}
		buscar = buscar->sig;
	}
}

void BuscarxNombre(char busca[],HWND ventana)
{
	wstring wxd;
	wstring comprobacion;
	Ps* indice = PERSONA;
	char comp[100];
	bool imprimir = false;
	while (indice != NULL)
	{
		strcpy_s(comp, indice->nombre);
		if (indice->nombrecompleto != "")
		{
			if (indice->carnet==true)
			{
				if (strcmp(comp, busca) == 0 && imprimir == false)
				{
					wxd = s2ws(indice->nombrecompleto);
					int point = SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_INSERTSTRING, 0, (LPARAM)wxd.c_str());
					SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_SETITEMDATA, point, (LPARAM)indice);
					imprimir = true;
				}
				strcpy_s(comp, indice->apellidop);
				if (strcmp(comp, busca) == 0 && imprimir == false)
				{
					wxd = s2ws(indice->nombrecompleto);
					int point = SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_INSERTSTRING, 0, (LPARAM)wxd.c_str());
					SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_SETITEMDATA, point, (LPARAM)indice);
					imprimir = true;
				}
				strcpy_s(comp, indice->apellidom);
				if (strcmp(comp, busca) == 0 && imprimir == false)
				{
					wxd = s2ws(indice->nombrecompleto);
					int point = SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_INSERTSTRING, 0, (LPARAM)wxd.c_str());
					SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_SETITEMDATA, point, (LPARAM)indice);
					imprimir = true;
				}
				strcpy_s(comp, indice->nombrecompleto);
				if (strcmp(comp, busca) == 0 && imprimir == false)
				{
					wxd = s2ws(indice->nombrecompleto);
					int point = SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_INSERTSTRING, 0, (LPARAM)wxd.c_str());
					SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_SETITEMDATA, point, (LPARAM)indice);
					imprimir = true;
				}
			}
		}
		indice = indice->sig;
		imprimir = false;
	}
	return;
}
void buscarbinaria(HWND ventana,int buscar)
{
	int conteo = 0;
	carnet* lista = CARNET;
	while (lista != NULL)
	{
		conteo++;
		lista = lista->sig;
	}
	//aqui empuieza "la busqueda binaria"
	float mitad = conteo / 2;
	carnet* ApBuscar=CARNET;
	wstring wimprimir;
	for (int i = 0; i <= conteo; i++)
	{
		ApBuscar = CARNET;
		for (int j = 1; j < mitad; j++)
		{
			ApBuscar = ApBuscar->sig;
		}

		if (buscar == ApBuscar->ID)
		{
			Ps* persona5 = buscarcurp(ApBuscar->CURP);
			wimprimir = s2ws(persona5->nombrecompleto);
			int point = SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_INSERTSTRING, 0, (LPARAM)wimprimir.c_str());
			SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_SETITEMDATA, point, (LPARAM)persona5);
			conteo = 0;
		}
		else
		{
			if (buscar > ApBuscar->ID)
			{
				mitad = mitad +(mitad / 2);
			}
			else
			{
				mitad = mitad / 2;
			}
		}
		
	}
	
	return;
}

bool QuickShortFuncion(HWND ventana, int Cantidad_De_Carnets)
{
	carnet* lista = CARNET;
	Ps* nombre = NULL;
	string nombrecompleto;
	int cadena[MAX_LOADSTRING];
	char palabras[100];
	for (int i = 0; i < Cantidad_De_Carnets; i++)
	{
		nombre = buscarcurp(lista);
		nombrecompleto = nombre->nombrecompleto;
		strcpy_s(palabras, nombrecompleto.c_str());
		cadena[i] = palabras[0];
		lista = lista->sig;
	}
	
	quicksort(cadena,0,Cantidad_De_Carnets-1);
	int id = 0;
	int cant_personas = 0;
	nombre = PERSONA;
	while (nombre != NULL)
	{
		cant_personas++;
		nombre = nombre->sig;
	}

	lista = CARNET;
	
		
	
	bool Imprimio = false;
	SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_RESETCONTENT, 0, 0);
	for (int i = Cantidad_De_Carnets-1; i >= 0; i = i)
	{

		char palabra = cadena[i];
		nombre = buscarcurp(lista);

		char busqueda_nombre[30];
		wstring wnombre = s2ws(nombre->nombrecompleto);
		string snombre(wnombre.begin(), wnombre.end());
		strcpy_s(busqueda_nombre, snombre.c_str());
		
		if (palabra == busqueda_nombre[0] && id != lista->ID)
		{

			int point = SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_INSERTSTRING, 0, (LPARAM)wnombre.c_str());
			SendMessage(GetDlgItem(ventana, IDC_LIST1), LB_SETITEMDATA, point, (LPARAM)lista);

			id = lista->ID;
			Imprimio = true;
			i--;

		}
		lista = lista->sig;
		if (Imprimio == true)
		{
			lista = CARNET;
			Imprimio = false;
		}
	}



	return false;
}
void quicksort(int A[], int izq, int der)
{
	int i, j, x, aux;
	i = izq;
	j = der;
	x = A[(izq + der) / 2];
	do {
		while ((A[i] < x) && (j <= der))
		{
			i++;
		}

		while ((x < A[j]) && (j > izq))
		{
			j--;
		}

		if (i <= j)
		{
			aux = A[i]; A[i] = A[j]; A[j] = aux;
			i++;  j--;
		}

	} while (i <= j);

	
	if (izq < j)
		quicksort(A, izq, j);
	if (i < der)
		quicksort(A, i, der);
}

void heapify(int arr[], int n, int i)
{

	int largest = i;
	int l = 2 * i + 1; 
	int r = 2 * i + 2; 

	
	if (l < n && arr[l] > arr[largest])
		largest = l;

	
	if (r < n && arr[r] > arr[largest])
		largest = r;

	
	if (largest != i) {
		swap(arr[i], arr[largest]);

		
		heapify(arr, n, largest);
	}
}
void heapSort(int arr[], int n)
{

	
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	
	for (int i = n - 1; i >= 0; i--) {
		
		swap(arr[0], arr[i]);

		
		heapify(arr, i, 0);
	}
}

std::wstring s2ws(const std::string& s) {
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

