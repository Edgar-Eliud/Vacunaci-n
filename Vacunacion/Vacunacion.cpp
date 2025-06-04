// 1ra Entrega.cpp : Define el punto de entrada de la aplicación.
//

#include "framework.h"
#include "1ra Entrega.h"
#include <string>
#include <oleauto.h>
#include <commdlg.h>
#include <CommCtrl.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <conio.h>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LOADSTRING 100

using namespace std;

struct Usuario
{
    char ClaveUs[200];
    char Contrasena[200];
    char APaterno[200];
    char AMaterno[200];
    char Nombres[200];
    Usuario* Anterior;
    Usuario* Siguiente;
}*OrigenU;
struct Carnet
{
    int ID;
    char Nombre[200];
    char CURP[200];
    char Vacuna[200];
    char Dosis[200];
    char FechaD[200];
    char Lote[200];
    char CVacunacion[200];
    Carnet* Anterior;
    Carnet* Siguiente;
}*OrigenC;
struct Vacuna
{
    char tipo[200];
    char Marca[200];
    int NoDosis;
    char ClaveV[200];
    char Descrip[1000];
    float Precio;
    Vacuna* Anterior;
    Vacuna* Siguiente;
}*OrigenV;
struct Persona
{
    char APaterno[200];
    char AMaterno[200];
    char Nombres[200];
    char CURP[200];
    char RFC[200];
    char FechaN[200];
    char Calle[200];
    char Colonia[200];
    char Cuidad[200];
    char Estado[200];
    char ECivil[200];
    int Telefono;
    char DIdent[200];
    char Sexo[200];
    char GOcupacional[200];
    char PRiesgp[200];
    char Orden[200];
    Persona* Anterior;
    Persona* Siguiente;
}*OrigenP;

// Variables globales:
HINSTANCE hInst;                                // instancia actual
WCHAR szTitle[MAX_LOADSTRING];                  // Texto de la barra de título
WCHAR szWindowClass[MAX_LOADSTRING];            // nombre de clase de la ventana principal

// Declaraciones de funciones adelantadas incluidas en este módulo de código:

//Funciones y estructuras de usuarios (alta)
void AgregarUsuarioAlInicio(Usuario* User);
Usuario* AltaUser(string ClaveUs, string Contrasena, string APaterno, string AMaterno, string Nombre);
Usuario* ValidacionContrasena(string BuscarContrasena);
Usuario* ValidacionUsuario(string BuscarUsuario);

//Funciones y estructuras de Carnet (alta, baja, modificaciion)
void AgragarCarnetAlInicio(Carnet* carnet);
Carnet* AltaCarnet(string CURP, string Vacuna, string Dosis, string FechaD, string Lote, string CVacunacion, string NombreC, int ID);
void ModificarCarnet(string NombreCarnetBuscar, string CURP, string vacuna, string Dosis, string FechaD, string Lote, string CVacunacion);
Carnet* BuscarCarnet(string BuscarCarnet);
Carnet* BuscarCarnetValid(int BuscarCarnetID);
Carnet* BuscarCarnetBin(HWND hWnd, int BuscarCarnetBin);
Carnet* BuscarCarnetsec(string BuscarCarnet);
void BorrarCarnetEnMedioSec(string NombreCarnetBuscar);
void BorrarCarnetAlInicio();
void BorrarCarnetAlFinal();

//Funciones y estructuras de Vacunas (alta, baja, midificacion)
void AgregarVacunasAlInicio(Vacuna* vacuna);
Vacuna* AltaVacuna(string Tipo, string Marca, int NoDosis, string ClaveV, string Descrip, float Precio);
void ModificarVacuna(string NombreVacunaBuscar, string Tipo, string Marca, int NoMarca, string ClaveV, string Descrip, float Precio);
Vacuna* BuscarVacuna(string BuscarCarnet);
void BorrarVacunaEnMedioSec(string NombreVacunaBuscar);
void BorrarVacunaAlInicio();
void BorrarVacunaAlFinal();
Vacuna* ValidacionClaveVacuna(string BuscarClave);

//Funciones y estructuras de Personaq (alta, baja, modificacion)
void AgregarPersonaAlInicio(Persona* persona);
Persona* AltaPersona(string APaterno, string AMaterno, string Nombre, string CURP, string RFC, string FechaN, string Calle, string Colonia, string Ciudad, string Estado, string ECivil, int Telefono, string DInt, string Sexo, string GOcupacional, string PRiesgo);
void ModidficarPersona(string NombrePersonaBuscar, string APaterno, string AMaterno, string Nombre, string CURP, string RFC, string FechaN, string Calle, string Colonia, string Ciudad, string Estado, string ECivil, int Telefono, string DInt, string Sexo, string GOcupacional, string PRiesgo);
Persona* BuscarPersona(string BuscarPersona);
void BorrarPersonaEnMedioSec(string NombrePersonaBuscar);
void BorrarPersonaAlInicio();
void BorrarPersonaAlFinal();
Persona* ValidacionCURP(string BuscarCURP);
Persona* ValidacionRFC(string BuscarRFC);
Persona* ValidacionCURPInicial(string BuscarCURP);
Persona* ValidacionCURPEspacios(HWND hWnd, string BuscarCURP);
Persona* ValidacionRFCEspacios(HWND hWnd, string BuscarRFC);

//Funciones y estructuras de archivos binarios (alta, carga)
void GuardarArchivoUsuario();
void GuardarArchivoCarnet();
void GuardarArchivoVacuna();
void GuardarArchivoPersona();

void LeerArchivoUsuario();
void LeerArchivoCarnet();
void LeerArchivoVacuna();
void LeerArchivoPersona();

//Quicksort
void quicksort(int A[], int izq, int der);

//Heapsort
void heapify(int arr[], int n, int i);
void heapSort(int arr[], int n);


/*const int tamano = 10, MAXIMO = 1000;
void Quicksort(char Arr[], int Inicio, int Final);*/

//void quicksort(char* const, int, int);
//void swap(char* const, char* const);

//headsort
//void Heapsort(int Arreglo);
//void HacerOrden(int Arreglo, int Nodo, int fin);


ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
std::wstring s2ws(const std::string& s);
bool MenuOpciones(HWND VentanaID, long Opcion);
BOOL CALLBACK Callback_Dialog1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Callback_Dialog2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Callback_Dialog3(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Callback_Dialog4(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Callback_Dialog5(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Callback_Dialog6(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Callback_Dialog7(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Callback_Dialog8(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Callback_Dialog9(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Callback_Dialog10(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Callback_Dialog11(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Callback_Dialog12(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Callback_Dialog13(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Colocar código aquí.

    // Inicializar cadenas globales
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY1RAENTREGA, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Realizar la inicialización de la aplicación:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1RAENTREGA));

    MSG msg;

    LeerArchivoUsuario();
    LeerArchivoCarnet();
    LeerArchivoVacuna();
    LeerArchivoPersona();

    // Bucle principal de mensajes:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    GuardarArchivoUsuario();
    GuardarArchivoCarnet();
    GuardarArchivoVacuna();
    GuardarArchivoPersona();

    return (int) msg.wParam;
}



//
//  FUNCIÓN: MyRegisterClass()
//
//  PROPÓSITO: Registra la clase de ventana.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY1RAENTREGA);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClassExW(&wcex);
}

//
//   FUNCIÓN: InitInstance(HINSTANCE, int)
//
//   PROPÓSITO: Guarda el identificador de instancia y crea la ventana principal
//
//   COMENTARIOS:
//
//        En esta función, se guarda el identificador de instancia en una variable común y
//        se crea y muestra la ventana principal del programa.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Almacenar identificador de instancia en una variable global

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, SW_HIDE);
   UpdateWindow(hWnd);

   HWND Modal = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)Callback_Dialog1);
   ShowWindow(Modal, SW_SHOW);
   UpdateWindow(Modal);

   return TRUE;
}

//Menu
bool MenuOpciones(HWND VentanaID, long Opcion)
{
    switch (Opcion)
    {
    case ID_CARNET_NUEVOCARNET:
    {
        HWND noModal = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG3), NULL, (DLGPROC)Callback_Dialog3);
        ShowWindow(noModal, SW_SHOW);
        UpdateWindow(noModal);
        EndDialog(VentanaID, Opcion);
    } break;
    case ID_CARNET_MODIFICARCARNET:
    {
        HWND noModal = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG4), NULL, (DLGPROC)Callback_Dialog4);
        ShowWindow(noModal, SW_SHOW);
        UpdateWindow(noModal);
        EndDialog(VentanaID, Opcion);
    } break;
    case ID_CARNET_BORRARCARNET:
    {
        HWND noModal = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG5), NULL, (DLGPROC)Callback_Dialog5);
        ShowWindow(noModal, SW_SHOW);
        UpdateWindow(noModal);
        EndDialog(VentanaID, Opcion);
    } break;
    case ID_VACUNA_REGI:
    {
        HWND noModal = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG6), NULL, (DLGPROC)Callback_Dialog6);
        ShowWindow(noModal, SW_SHOW);
        UpdateWindow(noModal);
        EndDialog(VentanaID, Opcion);
    } break;
    case ID_VACUNA_MODIFICARVACUNA:
    {
        HWND noModal = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG9), NULL, (DLGPROC)Callback_Dialog9);
        ShowWindow(noModal, SW_SHOW);
        UpdateWindow(noModal);
        EndDialog(VentanaID, Opcion);
    }break;
    case ID_VACUNA_BORRARVACUNA:
    {
        HWND noModal = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG12), NULL, (DLGPROC)Callback_Dialog12);
        ShowWindow(noModal, SW_SHOW);
        UpdateWindow(noModal);
        EndDialog(VentanaID, Opcion);
    }break;
    case ID_PERSONA_NUEVAPERSONA:
    {
        HWND noModal = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG7), NULL, (DLGPROC)Callback_Dialog7);
        ShowWindow(noModal, SW_SHOW);
        UpdateWindow(noModal);
        EndDialog(VentanaID, Opcion);
    } break;
    case ID_PERSONA_MODIFICARPERSONA:
    {
        HWND noModal = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG11), NULL, (DLGPROC)Callback_Dialog11);
        ShowWindow(noModal, SW_SHOW);
        UpdateWindow(noModal);
        EndDialog(VentanaID, Opcion);
    }break;
    case ID_PERSONA_BORRARPERSONA:
    {
        HWND noModal = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG13), NULL, (DLGPROC)Callback_Dialog13);
        ShowWindow(noModal, SW_SHOW);
        UpdateWindow(noModal);
        EndDialog(VentanaID, Opcion);
    }break;
    case ID_OTROS_MANUALDEUSUARIO:
    {
        HWND noModal = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG8), NULL, (DLGPROC)Callback_Dialog8);
        ShowWindow(noModal, SW_SHOW);
        UpdateWindow(noModal);
        EndDialog(VentanaID, Opcion);
    } break;
    case ID_OTROS_CERRARSECI32777:
    {
        HWND noModal = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG10), NULL, (DLGPROC)Callback_Dialog10);
        ShowWindow(noModal, SW_SHOW);
        UpdateWindow(noModal);
        EndDialog(VentanaID, Opcion);
    } break;
    case ID_OTROS_CERRARSESI32778:
    {
        HWND noModal = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)Callback_Dialog1);
        ShowWindow(noModal, SW_SHOW);
        UpdateWindow(noModal);
        EndDialog(VentanaID, Opcion);
    } break;
    case IDM_EXIT:
    case WM_DESTROY:
        DestroyWindow(VentanaID);
        break;
    default: return false;
    }
    return true;
}
//Ventanas
//Ventana de Inicio de sesion
/*Validaciones Completas*/
BOOL CALLBACK Callback_Dialog1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)//Validaciones completas
{
    switch (message)
    {
    case WM_INITDIALOG:
    {
       // return (BOOL)TRUE;
    }break;
    case WM_COMMAND:
    {
        long wmId = LOWORD(wParam);
        if (MenuOpciones(hWnd, wmId))
        {
            return (BOOL)FALSE;
        }
        switch (wmId)
        {
            case IDC_BUTTON1:
            {
                TCHAR buffer2[255];
                TCHAR buffer[255];

                GetDlgItemText(hWnd, IDC_EDIT2, buffer2, 255);
                wstring wBCon(buffer2);
                string BCon(wBCon.begin(), wBCon.end());
                GetDlgItemText(hWnd, IDC_EDIT1, buffer, 255);
                wstring wBUS(buffer);
                string BUS(wBUS.begin(), wBUS.end());

                if (wBCon == L"" && wBUS == L"")
                {
                    MessageBox(hWnd, L"Falta contraseña o usuario", L"Error", 0);
                }
                else
                {
                    if (ValidacionContrasena(BCon) != NULL)
                    {
                        if (buffer == NULL)
                        {
                            MessageBox(hWnd, L"Falta contraseña o usuario", L"Error", 0);
                        }
                        if (ValidacionUsuario(BUS) != NULL)
                        {
                            HWND noModal = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG10), NULL, (DLGPROC)Callback_Dialog10);
                            ShowWindow(noModal, SW_SHOW);
                            UpdateWindow(noModal);
                            EndDialog(hWnd, wmId);
                        }
                        else
                        {
                            MessageBox(hWnd, L"Contraseña o usuario invalido ", L"Error", 0);
                        }
                    }
                    else
                    {
                        MessageBox(hWnd, L"Contraseña o usuario invalido ", L"Error", 0);
                    }

                }
             
            } break;
            case IDC_BUTTON2:
            {
                HWND noModal = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG2), NULL, (DLGPROC)Callback_Dialog2);
                ShowWindow(noModal, SW_SHOW);
                UpdateWindow(noModal);
                EndDialog(hWnd, wmId);
            } break;
       // default: return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
        EndPaint(hWnd, &ps);
    }break;
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }break;
    default: return (BOOL)FALSE;
    }

    return /*(BOOL)*/FALSE;
}
//Ventana de nuevo usuario
/*Validaciones Completas*/
BOOL CALLBACK Callback_Dialog2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
    {
        return (BOOL)TRUE;
    }break;
    case WM_COMMAND:
    {
        long wmId = LOWORD(wParam);
        if (MenuOpciones(hWnd, wmId))
        {
            return (BOOL)FALSE;
        }
        switch (wmId)
        {
        case IDC_BUTTON1:
        {
            TCHAR buffer2[255];
            TCHAR buffer[255];
            TCHAR buffer3[255];
            TCHAR buffer4[255];

            GetDlgItemText(hWnd, IDC_EDIT2, buffer2, 255);
            wstring wBCon(buffer2);
            string BCon(wBCon.begin(), wBCon.end());
            GetDlgItemText(hWnd, IDC_EDIT1, buffer, 255);
            wstring wBUS(buffer);
            string BUS(wBUS.begin(), wBUS.end());
            GetDlgItemText(hWnd, IDC_EDIT3, buffer3, 255);
            wstring wVAP(buffer3);
            string VAP(wVAP.begin(), wVAP.end());
            GetDlgItemText(hWnd, IDC_EDIT5, buffer4, 255);
            wstring wVName(buffer4);
            string VName(wVName.begin(), wVName.end());

            if (wBCon == L"")
            {
                MessageBox(hWnd, L"Falta contraseña", L"Error", 0);
            }
            else if (wBUS == L"")
            {
                MessageBox(hWnd, L"Falta usuario", L"Error", 0);
            }
            else if (wVAP == L"")
            {
                MessageBox(hWnd, L"Falta Apellido parterno", L"Error", 0);
            }
            else if (wVName == L"")
            {
                MessageBox(hWnd, L"Falta Nombre(s)", L"Error", 0);
            }
            else
            {
                TCHAR Buffer[255];
                GetDlgItemText(hWnd, IDC_EDIT1, Buffer, 255);
                wstring wCalveUs(Buffer);
                GetDlgItemText(hWnd, IDC_EDIT2, Buffer, 255);
                wstring wContrasenia(Buffer);
                GetDlgItemText(hWnd, IDC_EDIT3, Buffer, 255);
                wstring wAPaterno(Buffer);
                GetDlgItemText(hWnd, IDC_EDIT4, Buffer, 255);
                wstring wAMaterno(Buffer);
                GetDlgItemText(hWnd, IDC_EDIT5, Buffer, 255);
                wstring wNombre(Buffer);
                string ClaveUs(wCalveUs.begin(), wCalveUs.end());
                string Contrasenia(wContrasenia.begin(), wContrasenia.end());
                string APaterno(wAPaterno.begin(), wAPaterno.end());
                string AMaterno(wAMaterno.begin(), wAMaterno.end());
                string Nombre(wNombre.begin(), wNombre.end());
                Usuario* User = AltaUser(ClaveUs, Contrasenia, APaterno, AMaterno, Nombre);
                AgregarUsuarioAlInicio(User);

                HWND noModal = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG10), NULL, (DLGPROC)Callback_Dialog10);
                ShowWindow(noModal, SW_SHOW);
                UpdateWindow(noModal);
                EndDialog(hWnd, wmId);
            }
           
        } break;
        default: return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
        EndPaint(hWnd, &ps);
    }break;
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }break;
    default: return (BOOL)FALSE;
    }

    return (BOOL)FALSE;
}
//Ventana de Nuevo Carnet
BOOL CALLBACK Callback_Dialog3(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
    {
        //Carnet* ID = new Carnet;
        int IDNum = 310300;
        Carnet* IndiceC = OrigenC;
        //IndiceC->ID = IDNum;
        while (IndiceC != NULL)
        {
            IndiceC->ID = IDNum;
            IndiceC = IndiceC->Siguiente;
            IDNum++;
        }
        if (IndiceC == NULL)
        {
            int IDRes = IDNum;
            wstring ID = to_wstring(IDRes);
            SetDlgItemText(hWnd, IDC_EDIT7, ID.c_str());
        }
        return (BOOL)TRUE;
    }break;
    case WM_COMMAND:
    {
        long wmId = LOWORD(wParam);
        if (MenuOpciones(hWnd, wmId))
        {
            return (BOOL)FALSE;
        }
        switch (wmId)
        {
        case IDC_BUTTON1:
        {
            TCHAR buffer[255];
            TCHAR buffer2[255];
            SYSTEMTIME Date;

            DateTime_GetSystemtime(GetDlgItem(hWnd, IDC_DATETIMEPICKER1), &Date);
            GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, &Date, NULL, buffer, 255);

            GetDlgItemText(hWnd, IDC_EDIT7, buffer2, 255);
            int IDs = _wtoi(buffer2);
            GetDlgItemText(hWnd, IDC_EDIT1, buffer2, 255);
            wstring wCURP(buffer2);
            GetDlgItemText(hWnd, IDC_EDIT2, buffer2, 255);
            wstring wVacuna(buffer2);
            GetDlgItemText(hWnd, IDC_EDIT3, buffer2, 255);
            wstring wDosis(buffer2);
            GetDlgItemText(hWnd, IDC_EDIT5, buffer2, 255);
            wstring wLote(buffer2);
            GetDlgItemText(hWnd, IDC_EDIT6, buffer2, 255);
            wstring wCVacunacion(buffer2);
            GetDlgItemText(hWnd, IDC_EDIT4, buffer2, 255);
            wstring wNombreC(buffer2);
            wstring wFecha(buffer);
            string CURP(wCURP.begin(), wCURP.end());
            string Vacuna(wVacuna.begin(), wVacuna.end());
            string Dosis(wDosis.begin(), wDosis.end());
            string Lote(wLote.begin(), wLote.end());
            string CVacuna(wCVacunacion.begin(), wCVacunacion.end());
            string NombreC(wNombreC.begin(), wNombreC.end());
            string Fecha(wFecha.begin(), wFecha.end());
           //string IDs(wIDs.begin(), wIDs.end());
            Carnet* carnet = AltaCarnet(CURP, Vacuna, Dosis, Lote, CVacuna, Fecha, NombreC, IDs);
            AgragarCarnetAlInicio(carnet);

            GetDlgItemText(hWnd, IDC_EDIT1, buffer, 255);
            SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)buffer);

            HWND noModal = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG3), NULL, (DLGPROC)Callback_Dialog3);
            ShowWindow(noModal, SW_SHOW);
            UpdateWindow(noModal);
            EndDialog(hWnd, wmId);
        } break;
        case IDC_BUTTON2:
        {
            TCHAR buffer2[255];
            TCHAR buffer[255];

            GetDlgItemText(hWnd, IDC_EDIT8, buffer2, 255);
            wstring wBPer(buffer2);
            string BPer(wBPer.begin(), wBPer.end());

            if (BuscarPersona(BPer) != NULL)
            {
                SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_RESETCONTENT, 0, 0);
                Persona* IndiceP = OrigenP;
                while (IndiceP->APaterno != NULL)
                {

                    if (IndiceP->APaterno != BPer)
                    {
                        IndiceP = IndiceP->Siguiente;
                    }
                    else if (IndiceP->APaterno == BPer)
                    {
                        wstring wBPer = s2ws(IndiceP->APaterno).append(L" ").append(s2ws(IndiceP->AMaterno)).append(L" ").append(s2ws(IndiceP->Nombres));
                        int posicion = SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_INSERTSTRING, 0, (LPARAM)wBPer.c_str());
                        SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_SETITEMDATA, posicion, (LPARAM)IndiceP);
                        IndiceP = IndiceP->Siguiente;
                    }
                }
            }
            else
            {
                MessageBox(hWnd, L"La persona no se encontro o no existe Σ(っ °Д °;)っ", L"Error", 0);
            }
        }
        case IDC_LIST1:
        {
            long Notificacion = HIWORD(wParam);
            switch (Notificacion)
            {
            case LBN_SELCHANGE:
            {
                int Seleccion = SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_GETCURSEL, 0, 0);
                if (Seleccion >= 0)
                {
                    Persona* Seleccionado = (Persona*)SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_GETITEMDATA, Seleccion, 0);
                    SetDlgItemText(hWnd, IDC_EDIT1, s2ws(Seleccionado->CURP).c_str());

                }
            }break;
            default:return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }break;
        default: return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
        EndPaint(hWnd, &ps);
    }break;
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }break;
    default: return (BOOL)FALSE;
    }

    return (BOOL)FALSE;
}
//Ventana de modificacion de carnet
BOOL CALLBACK Callback_Dialog4(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
    {
        return (BOOL)TRUE;
    }break;
    case WM_COMMAND:
    {
        long wmId = LOWORD(wParam);
        if (MenuOpciones(hWnd, wmId))
        {
            return (BOOL)FALSE;
        }
        switch (wmId)
        {
        case IDC_BUTTON1:
        {
            TCHAR buffer[255];
            TCHAR buffer2[255];
            SYSTEMTIME Date;

            DateTime_GetSystemtime(GetDlgItem(hWnd, IDC_DATETIMEPICKER1), &Date);
            GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, &Date, NULL, buffer, 255);

            GetDlgItemText(hWnd, IDC_EDIT4, buffer2, 255);
            wstring wNombreCB(buffer2);
            GetDlgItemText(hWnd, IDC_EDIT1, buffer2, 255);
            wstring wCURP(buffer2);
            GetDlgItemText(hWnd, IDC_EDIT2, buffer2, 255);
            wstring wVacuna(buffer2);
            GetDlgItemText(hWnd, IDC_EDIT3, buffer2, 255);
            wstring wDosis(buffer2);
            GetDlgItemText(hWnd, IDC_EDIT5, buffer2, 255);
            wstring wLote(buffer2);
            GetDlgItemText(hWnd, IDC_EDIT6, buffer2, 255);
            wstring wCVacunacion(buffer2);
            GetDlgItemText(hWnd, IDC_EDIT4, buffer2, 255);
            wstring wNombreC(buffer2);
            wstring wFecha(buffer);
            string NombreCB(wNombreCB.begin(), wNombreCB.end());
            string CURP(wCURP.begin(), wCURP.end());
            string Vacuna(wVacuna.begin(), wVacuna.end());
            string Dosis(wDosis.begin(), wDosis.end());
            string Lote(wLote.begin(), wLote.end());
            string CVacuna(wCVacunacion.begin(), wCVacunacion.end());
            string NombreC(wNombreC.begin(), wNombreC.end());
            string Fecha(wFecha.begin(), wFecha.end());
            ModificarCarnet(NombreCB, CURP, Vacuna, Dosis, Fecha, Lote, CVacuna);

            GetDlgItemText(hWnd, IDC_EDIT1, buffer, 255);
            SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)buffer);

        }break;
        case IDC_BUTTON2:
        {
            TCHAR buffer2[255];
            TCHAR buffer[255];

            GetDlgItemText(hWnd, IDC_EDIT4, buffer2, 255);
            wstring wBSecuencial(buffer2);
            string BSecuencial(wBSecuencial.begin(), wBSecuencial.end());

            if (BuscarCarnetsec(BSecuencial) != NULL)
            {
                SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_RESETCONTENT, 0, 0);
                Carnet* IndiceC = OrigenC;
                while (IndiceC->Nombre != BSecuencial)
                {
                    IndiceC = IndiceC->Siguiente;
                }
                if (IndiceC->Nombre == BSecuencial)
                {
                    wstring wNombrePro = s2ws(IndiceC->Nombre).append(L" - ").append(s2ws(IndiceC->CURP));
                    int posicion = SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_INSERTSTRING, 0, (LPARAM)wNombrePro.c_str());
                    SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_SETITEMDATA, posicion, (LPARAM)IndiceC);
                }
            }
            else
            {
                MessageBox(hWnd, L"El carnet no se encontro o no existe", L"Error", 0);
            }
            

        }break;
        case IDC_BUTTON3:
        {
            TCHAR buffer2[255];
            TCHAR buffer[255];

            GetDlgItemText(hWnd, IDC_EDIT7, buffer2, 255);
            int BBinary = _wtoi(buffer2);
            //string BBinary(wBBinary.begin(), wBBinary.end());
            if (BuscarCarnetValid == NULL)
            {
                MessageBox(hWnd, L"no hay carnets existentes", L"erorr", 0);
            }
            else
            {
                if (BuscarCarnetBin(hWnd, BBinary) != NULL)
                {
                    SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_RESETCONTENT, 0, 0);
                    Carnet* IndiceC = OrigenC;
                    while (IndiceC->ID != BBinary)
                    {
                        IndiceC = IndiceC->Siguiente;
                    }
                    if (IndiceC->ID == BBinary)
                    {
                        wstring wNombrePro = s2ws(IndiceC->Nombre).append(L" - ").append(s2ws(IndiceC->CURP));
                        int posicion = SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_INSERTSTRING, 0, (LPARAM)wNombrePro.c_str());
                        SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_SETITEMDATA, posicion, (LPARAM)IndiceC);
                    }
                }
                else
                {
                    MessageBox(hWnd, L"El carnet no se encontro o no existe", L"Error", 0);
                }
            }
           
        }break;
        case IDC_LIST1:
        {
            long Notificacion = HIWORD(wParam);
            switch (Notificacion)
            {
            case LBN_SELCHANGE:
            {
                int Seleccion = SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_GETCURSEL, 0, 0);
                if (Seleccion >= 0)
                {
                    Carnet* Seleccionado = (Carnet*)SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_GETITEMDATA, Seleccion, 0);
                    SetDlgItemText(hWnd, IDC_EDIT1, s2ws(Seleccionado->CURP).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT2, s2ws(Seleccionado->Vacuna).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT3, s2ws((Seleccionado->Dosis)).c_str());
                    SetDlgItemText(hWnd, IDC_DATETIMEPICKER1, s2ws(Seleccionado->FechaD).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT5, s2ws((Seleccionado->Lote)).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT6, s2ws((Seleccionado->CVacunacion)).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT8, s2ws(to_string(Seleccionado->ID)).c_str());

                }
            }break;
            default:return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }break;
        default: return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
        EndPaint(hWnd, &ps);
    }break;
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }break;
    default: return (BOOL)FALSE;
    }

    return (BOOL)FALSE;
}
//vantana de borrar carnet
BOOL CALLBACK Callback_Dialog5(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
    {
        return (BOOL)TRUE;
    }break;
    case WM_COMMAND:
    {
        long wmId = LOWORD(wParam);
        if (MenuOpciones(hWnd, wmId))
        {
            return (BOOL)FALSE;
        }
        switch (wmId)
        {
        case IDC_BUTTON1:
        {
            TCHAR buffer2[255];
            TCHAR buffer[255];

            GetDlgItemText(hWnd, IDC_EDIT1, buffer2, 255);
            wstring wBSecuencial(buffer2);
            string BSecuencial(wBSecuencial.begin(), wBSecuencial.end());

            if (BuscarCarnetsec(BSecuencial) != NULL)
            {
                SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_RESETCONTENT, 0, 0);
                Carnet* IndiceC = OrigenC;
                while (IndiceC->Nombre != BSecuencial)
                {
                    IndiceC = IndiceC->Siguiente;
                }
                if (IndiceC->Nombre == BSecuencial)
                {
                    wstring wNombrePro = s2ws(IndiceC->Nombre).append(L" - ").append(s2ws(IndiceC->CURP));
                    int posicion = SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_INSERTSTRING, 0, (LPARAM)wNombrePro.c_str());
                    SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_SETITEMDATA, posicion, (LPARAM)IndiceC);
                }
            }
            else
            {
                MessageBox(hWnd, L"El carnet no se encontro o no existe", L"Error", 0);
            }
        }break;
        case IDC_BUTTON2:
        {
            TCHAR buffer2[255];
            GetDlgItemText(hWnd, IDC_EDIT1, buffer2, 255);
            wstring wBCar(buffer2);
            string BCar(wBCar.begin(), wBCar.end());
            BorrarCarnetEnMedioSec(BCar);

            int Seleccion = SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_GETCURSEL, 0, 0);
            if (Seleccion >= 0)
            {
                SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_DELETESTRING, Seleccion, 0);
            }
        }break;
        case IDC_BUTTON3:
        {

        }break;
        default: return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
        EndPaint(hWnd, &ps);
    }break;
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }break;
    default: return (BOOL)FALSE;
    }

    return (BOOL)FALSE;
}
//Vantana de nueva vacuna
BOOL CALLBACK Callback_Dialog6(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
    {
        return (BOOL)TRUE;
    }break;
    case WM_COMMAND:
    {
        long wmId = LOWORD(wParam);
        if (MenuOpciones(hWnd, wmId))
        {
            return (BOOL)FALSE;
        }
        switch (wmId)
        {
            case IDC_BUTTON1 :
            {
                TCHAR buffer[255];
                TCHAR buffer2[1000];
                GetDlgItemText(hWnd, IDC_EDIT1, buffer, 255);
                wstring wTipo(buffer);
                GetDlgItemText(hWnd, IDC_EDIT2, buffer, 255);
                wstring wMarca(buffer);
                GetDlgItemText(hWnd, IDC_EDIT3, buffer, 255);
                int NoDosis = _wtoi(buffer);
                GetDlgItemText(hWnd, IDC_EDIT4, buffer, 255);
                wstring wCVacuna(buffer);
                GetDlgItemText(hWnd, IDC_EDIT5, buffer2, 1000);
                wstring wDescrip(buffer);
                GetDlgItemText(hWnd, IDC_EDIT6, buffer, 255);
                float Precio = _wtof(buffer);
                string Tipo(wTipo.begin(), wTipo.end());
                string Marca(wMarca.begin(), wMarca.end());
                string CVacuna(wCVacuna.begin(), wCVacuna.end());
                string Descrip(wDescrip.begin(), wDescrip.end());
                if (Precio > 0)
                {
                    if (ValidacionClaveVacuna(CVacuna) == NULL)
                    {
                        Vacuna* vacuna = AltaVacuna(Tipo, Marca, NoDosis, CVacuna, Descrip, Precio);
                        AgregarVacunasAlInicio(vacuna);

                        HWND noModal = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG6), NULL, (DLGPROC)Callback_Dialog6);
                        ShowWindow(noModal, SW_SHOW);
                        UpdateWindow(noModal);
                        EndDialog(hWnd, wmId);
                    }
                    else
                    {
                        MessageBox(hWnd, L"Clave de vacuna ya registrada", L"Error", 0);

                    }
                    
                }
                else
                {
                    MessageBox(hWnd, L"Las vacunas no son gratis", L"Error", 0);
                }
                


                GetDlgItemText(hWnd, IDC_EDIT2, buffer, 255);
                SendMessage(GetDlgItem(hWnd, IDC_LIST2), LB_ADDSTRING, 0, (LPARAM)buffer);
            }break;
        default: return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
        EndPaint(hWnd, &ps);
    }break;
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }break;
    default: return (BOOL)FALSE;
    }

    return (BOOL)FALSE;
}
//Ventana de nueva persona
BOOL CALLBACK Callback_Dialog7(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
    {
        return (BOOL)TRUE;
    }break;
    case WM_COMMAND:
    {
        long wmId = LOWORD(wParam);
        if (MenuOpciones(hWnd, wmId))
        {
            return (BOOL)FALSE;
        }
        switch (wmId)
        {
            case IDC_BUTTON1:
            {
                TCHAR buffer3[255];
                TCHAR buffer4[255];

                GetDlgItemText(hWnd, IDC_EDIT3, buffer3, 255);
                wstring wCURP(buffer3);
                string CURP(wCURP.begin(), wCURP.end());
                GetDlgItemText(hWnd, IDC_EDIT4, buffer4, 255);
                wstring wRFC(buffer4);
                string RFC(wRFC.begin(), wRFC.end());

                if (wCURP == L"")
                {
                    MessageBox(hWnd, L"Falta CURP", L"Error", 0);
                }
                else if (wRFC == L"")
                {
                    MessageBox(hWnd, L"Falta RFC", L"Error", 0);
                }
                else
                {
                    if (ValidacionCURP(CURP) == NULL && ValidacionCURPEspacios(hWnd, CURP) == NULL)
                    {
                        if (ValidacionRFC(RFC) == NULL && ValidacionRFCEspacios(hWnd, RFC) == NULL)
                        {
                            TCHAR buffer[255];
                            SYSTEMTIME Date;

                            DateTime_GetSystemtime(GetDlgItem(hWnd, IDC_DATETIMEPICKER1), &Date);
                            GetDateFormat(LOCALE_USER_DEFAULT, DATE_SHORTDATE, &Date, NULL, buffer, 255);

                            GetDlgItemText(hWnd, IDC_EDIT1, buffer, 255);
                            wstring waMaterno(buffer);
                            GetDlgItemText(hWnd, IDC_EDIT2, buffer, 255);
                            wstring wNombre(buffer);
                            GetDlgItemText(hWnd, IDC_EDIT3, buffer, 255);
                            wstring wCURP(buffer);
                            GetDlgItemText(hWnd, IDC_EDIT4, buffer, 255);
                            wstring wRFC(buffer);
                            GetDlgItemText(hWnd, IDC_EDIT6, buffer, 255);
                            wstring wCalle(buffer);
                            GetDlgItemText(hWnd, IDC_EDIT7, buffer, 255);
                            wstring wColonia(buffer);
                            GetDlgItemText(hWnd, IDC_EDIT8, buffer, 255);
                            wstring wCuiudad(buffer);
                            GetDlgItemText(hWnd, IDC_EDIT9, buffer, 255);
                            wstring wAPaterno(buffer);
                            GetDlgItemText(hWnd, IDC_EDIT10, buffer, 255);
                            wstring wEstado(buffer);
                            GetDlgItemText(hWnd, IDC_EDIT11, buffer, 255);
                            wstring wECivil(buffer);
                            GetDlgItemText(hWnd, IDC_EDIT12, buffer, 255);
                            int Telefono = _wtoi(buffer);
                            GetDlgItemText(hWnd, IDC_IMAGEN1, buffer, 255);
                            wstring wDIdent(buffer);
                            GetDlgItemText(hWnd, IDC_EDIT14, buffer, 255);
                            wstring wSexo(buffer);
                            GetDlgItemText(hWnd, IDC_EDIT15, buffer, 255);
                            wstring wGOcu(buffer);
                            GetDlgItemText(hWnd, IDC_EDIT16, buffer, 255);
                            wstring wFechaN(buffer);
                            wstring wPRiesgo(buffer);
                            string aMaterno(waMaterno.begin(), waMaterno.end());
                            string Nombre(wNombre.begin(), wNombre.end());
                            string CURP(wCURP.begin(), wCURP.end());
                            string RFC(wRFC.begin(), wRFC.end());
                            string Calle(wCalle.begin(), wCalle.end());
                            string Colonia(wColonia.begin(), wColonia.end());
                            string Cuiudad(wCuiudad.begin(), wCuiudad.end());
                            string APaterno(wAPaterno.begin(), wAPaterno.end());
                            string Estado(wEstado.begin(), wEstado.end());
                            string ECivil(wECivil.begin(), wECivil.end());
                            string DIdent(wDIdent.begin(), wDIdent.end());
                            string Sexo(wSexo.begin(), wSexo.end());
                            string GOcu(wGOcu.begin(), wGOcu.end());
                            string PRiesgo(wPRiesgo.begin(), wPRiesgo.end());
                            string FechaN(wFechaN.begin(), wFechaN.end());
                            Persona* persona = AltaPersona(APaterno, aMaterno, Nombre, CURP, RFC, FechaN, Calle, Colonia, Cuiudad, Estado, ECivil, Telefono, DIdent, Sexo, GOcu, PRiesgo);
                            AgregarPersonaAlInicio(persona);

                            HWND noModal = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG7), NULL, (DLGPROC)Callback_Dialog7);
                            ShowWindow(noModal, SW_SHOW);
                            UpdateWindow(noModal);
                            EndDialog(hWnd, wmId);
                        }
                        
                    }
                    else
                    {
                        if (ValidacionCURP(CURP) != NULL && ValidacionCURPEspacios(hWnd, CURP) != NULL)
                        {
                            if (ValidacionRFC(RFC) != NULL && ValidacionRFCEspacios(hWnd, RFC) != NULL)
                            {
                                TCHAR buffer[255];
                                SYSTEMTIME Date;

                                DateTime_GetSystemtime(GetDlgItem(hWnd, IDC_DATETIMEPICKER1), &Date);
                                GetDateFormat(LOCALE_USER_DEFAULT, DATE_SHORTDATE, &Date, NULL, buffer, 255);

                                GetDlgItemText(hWnd, IDC_EDIT1, buffer, 255);
                                wstring waMaterno(buffer);
                                GetDlgItemText(hWnd, IDC_EDIT2, buffer, 255);
                                wstring wNombre(buffer);
                                GetDlgItemText(hWnd, IDC_EDIT3, buffer, 255);
                                wstring wCURP(buffer);
                                GetDlgItemText(hWnd, IDC_EDIT4, buffer, 255);
                                wstring wRFC(buffer);
                                GetDlgItemText(hWnd, IDC_EDIT6, buffer, 255);
                                wstring wCalle(buffer);
                                GetDlgItemText(hWnd, IDC_EDIT7, buffer, 255);
                                wstring wColonia(buffer);
                                GetDlgItemText(hWnd, IDC_EDIT8, buffer, 255);
                                wstring wCuiudad(buffer);
                                GetDlgItemText(hWnd, IDC_EDIT9, buffer, 255);
                                wstring wAPaterno(buffer);
                                GetDlgItemText(hWnd, IDC_EDIT10, buffer, 255);
                                wstring wEstado(buffer);
                                GetDlgItemText(hWnd, IDC_EDIT11, buffer, 255);
                                wstring wECivil(buffer);
                                GetDlgItemText(hWnd, IDC_EDIT12, buffer, 255);
                                int Telefono = _wtoi(buffer);
                                GetDlgItemText(hWnd, IDC_IMAGEN1, buffer, 255);
                                wstring wDIdent(buffer);
                                GetDlgItemText(hWnd, IDC_EDIT14, buffer, 255);
                                wstring wSexo(buffer);
                                GetDlgItemText(hWnd, IDC_EDIT15, buffer, 255);
                                wstring wGOcu(buffer);
                                GetDlgItemText(hWnd, IDC_EDIT16, buffer, 255);
                                wstring wFechaN(buffer);
                                wstring wPRiesgo(buffer);
                                string aMaterno(waMaterno.begin(), waMaterno.end());
                                string Nombre(wNombre.begin(), wNombre.end());
                                string CURP(wCURP.begin(), wCURP.end());
                                string RFC(wRFC.begin(), wRFC.end());
                                string Calle(wCalle.begin(), wCalle.end());
                                string Colonia(wColonia.begin(), wColonia.end());
                                string Cuiudad(wCuiudad.begin(), wCuiudad.end());
                                string APaterno(wAPaterno.begin(), wAPaterno.end());
                                string Estado(wEstado.begin(), wEstado.end());
                                string ECivil(wECivil.begin(), wECivil.end());
                                string DIdent(wDIdent.begin(), wDIdent.end());
                                string Sexo(wSexo.begin(), wSexo.end());
                                string GOcu(wGOcu.begin(), wGOcu.end());
                                string PRiesgo(wPRiesgo.begin(), wPRiesgo.end());
                                string FechaN(wFechaN.begin(), wFechaN.end());
                                Persona* persona = AltaPersona(APaterno, aMaterno, Nombre, CURP, RFC, FechaN, Calle, Colonia, Cuiudad, Estado, ECivil, Telefono, DIdent, Sexo, GOcu, PRiesgo);
                                AgregarPersonaAlInicio(persona);

                                HWND noModal = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG7), NULL, (DLGPROC)Callback_Dialog7);
                                ShowWindow(noModal, SW_SHOW);
                                UpdateWindow(noModal);
                                EndDialog(hWnd, wmId);
                            }
                            else
                            {
                                MessageBox(hWnd, L"RFC ya existente ", L"Error", 0);
                            }
                        }
                        else
                        {
                            MessageBox(hWnd, L"CURP ya existente ", L"Error", 0);
                        }
                    }
                   
                }

                
                TCHAR buffer5[255];
                GetDlgItemText(hWnd, IDC_EDIT9, buffer5, 255);
                wstring wAPaterno(buffer5);
                
                
                GetDlgItemText(hWnd, IDC_EDIT9, buffer5, 255);
                SendMessage(GetDlgItem(hWnd, IDC_LIST3), LB_ADDSTRING, 0, (LPARAM)buffer5);
            }break;
            case IDC_BUTTON2:
            {
                OPENFILENAME ofn;
                WCHAR FileName[1000] = { 0 };
                ZeroMemory(&ofn, sizeof(ofn));
                ofn.lStructSize = sizeof(OPENFILENAME);
                ofn.hwndOwner = hWnd;
                ofn.lpstrFile = FileName;
                ofn.nMaxFile = 1000;
                ofn.lpstrFilter = L"Imagen BMP\0*.bmp\0";
                ofn.nFilterIndex = 1;
                ofn.lpstrTitle = NULL;
                ofn.nMaxFileTitle = 0;
                ofn.lpstrInitialDir = NULL;
                ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

                if (GetOpenFileName(&ofn) == TRUE)
                {
                    HBITMAP imagen;
                    imagen = (HBITMAP)LoadImage(hInst, FileName, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE | LR_DEFAULTCOLOR | LR_DEFAULTSIZE);
                    if (imagen == NULL)
                    {
                        MessageBox(hWnd, L"Error: No se pudo abrir la imagen", L"Image error", 0);
                    }
                    else
                    {
                        SendDlgItemMessage(hWnd, IDC_IMAGEN1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                    }
                }
            }break;
        default: return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
        EndPaint(hWnd, &ps);
    }break;
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }break;
    default: return (BOOL)FALSE;
    }

    return (BOOL)FALSE;
}
//Ventana de manual de usuario (aun sin funcionalidad)
BOOL CALLBACK Callback_Dialog8(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
    {
        return (BOOL)TRUE;
    }break;
    case WM_COMMAND:
    {
        long wmId = LOWORD(wParam);
        if (MenuOpciones(hWnd, wmId))
        {
            return (BOOL)FALSE;
        }
        switch (wmId)
        {
        default: return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
        EndPaint(hWnd, &ps);
    }break;
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }break;
    default: return (BOOL)FALSE;
    }

    return (BOOL)FALSE;
}
//Ventana de modificacion de Vacuna
BOOL CALLBACK Callback_Dialog9(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
    {
        return (BOOL)TRUE;
    }break;
    case WM_COMMAND:
    {
        long wmId = LOWORD(wParam);
        if (MenuOpciones(hWnd, wmId))
        {
            return (BOOL)FALSE;
        }
        switch (wmId)
        {
        case IDC_BUTTON1:
        {
            TCHAR buffer2[255];
            TCHAR buffer[255];

            GetDlgItemText(hWnd, IDC_EDIT1, buffer2, 255);
            wstring wBVac(buffer2);
            string BVac(wBVac.begin(), wBVac.end());

            if (BuscarVacuna(BVac) != NULL)
            {
                SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_RESETCONTENT, 0, 0);
                Vacuna* IndiceV = OrigenV;
                while (IndiceV->ClaveV != BVac)
                {
                    IndiceV = IndiceV->Siguiente;
                }
                if (IndiceV->ClaveV == BVac)
                {
                    wstring wNombrePro = s2ws(IndiceV->ClaveV).append(L" - ").append(s2ws(IndiceV->Marca));
                    int posicion = SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_INSERTSTRING, 0, (LPARAM)wBVac.c_str());
                    SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_SETITEMDATA, posicion, (LPARAM)IndiceV);
                }
            }
            else
            {
                MessageBox(hWnd, L"La vacuna no se encontro o no esta registrada", L"Error", 0);
            }

        }break;
        case IDC_BUTTON2:
        {
            TCHAR buffer[255];
            TCHAR buffer2[1000];

            GetDlgItemText(hWnd, IDC_EDIT2, buffer, 255);
            wstring wTipo(buffer);
            GetDlgItemText(hWnd, IDC_EDIT3, buffer, 255);
            wstring wMarca(buffer);
            GetDlgItemText(hWnd, IDC_EDIT4, buffer, 255);
            int NoDosis = _wtoi(buffer);
            GetDlgItemText(hWnd, IDC_EDIT5, buffer, 255);
            wstring wCVacuna(buffer);
            GetDlgItemText(hWnd, IDC_EDIT6, buffer2, 1000);
            wstring wDescrip(buffer);
            GetDlgItemText(hWnd, IDC_EDIT7, buffer, 255);
            float Precio = _wtof(buffer);
            string Tipo(wTipo.begin(), wTipo.end());
            string Marca(wMarca.begin(), wMarca.end());
            string CVacuna(wCVacuna.begin(), wCVacuna.end());
            string Descrip(wDescrip.begin(), wDescrip.end());
            ModificarVacuna(CVacuna, Tipo, Marca, NoDosis, CVacuna, Descrip, Precio);

            GetDlgItemText(hWnd, IDC_EDIT2, buffer, 255);
            SendMessage(GetDlgItem(hWnd, IDC_LIST2), LB_ADDSTRING, 0, (LPARAM)buffer);

        }break;
        case IDC_LIST1:
        {
            long Notificacion = HIWORD(wParam);
            switch (Notificacion)
            {
            case LBN_SELCHANGE:
            {
                int Seleccion = SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_GETCURSEL, 0, 0);
                if (Seleccion >= 0)
                {
                    Vacuna* Seleccionado = (Vacuna*)SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_GETITEMDATA, Seleccion, 0);
                    SetDlgItemText(hWnd, IDC_EDIT2, s2ws(Seleccionado->tipo).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT3, s2ws(Seleccionado->Marca).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT4, s2ws(to_string(Seleccionado->NoDosis)).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT5, s2ws((Seleccionado->ClaveV)).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT6, s2ws((Seleccionado->Descrip)).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT7, s2ws(to_string(Seleccionado->Precio)).c_str());

                }
            }
            }
        }break;
        default: return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
        EndPaint(hWnd, &ps);
    }break;
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }break;
    default: return (BOOL)FALSE;
    }

    return (BOOL)FALSE;
}
//Ventana de Pagina de incio
BOOL CALLBACK Callback_Dialog10(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
    {
        SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_RESETCONTENT, 0, 0);
        Carnet* IndiceC = OrigenC;
        while (IndiceC != NULL)
        {
            int array[100];
            bool ciclo = false;
            char conf[100];
            int numero = 0;
            strcpy_s(conf, 100, OrigenC->Siguiente->Nombre);
            while (IndiceC != NULL && ciclo == false)
            {

                array[numero] = IndiceC->ID;

                if (strcmp(conf, IndiceC->Nombre) == 0)
                {
                    ciclo = true;
                }
                numero++;
                IndiceC = IndiceC->Siguiente;

            }

            heapSort(array, numero);
            IndiceC = OrigenC;
            for (int i = numero - 1; i >= 0; i = i)
            {
                int letra = array[i];


                if (letra == IndiceC->ID)
                {
                    wstring wClaveUs = s2ws(IndiceC->Nombre).append(L" - ").append(s2ws(to_string(IndiceC->ID)));
                    int posicion = SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_INSERTSTRING, 0, (LPARAM)wClaveUs.c_str());
                    SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_SETITEMDATA, posicion, (LPARAM)IndiceC);
                    i--;
                }
                IndiceC = IndiceC->Siguiente;
                if (IndiceC == NULL)
                {
                    IndiceC = OrigenC;
                }
            }
        }
        

        SendMessage(GetDlgItem(hWnd, IDC_LIST2), LB_RESETCONTENT, 0, 0);
        Vacuna* IndiceV = OrigenV;
        while (IndiceV != NULL)
        {
            wstring wMarca = s2ws(IndiceV->ClaveV).append(L" - ").append(s2ws(IndiceV->Marca));
            int posicion = SendMessage(GetDlgItem(hWnd, IDC_LIST2), LB_INSERTSTRING, 0, (LPARAM)wMarca.c_str());
            SendMessage(GetDlgItem(hWnd, IDC_LIST2), LB_SETITEMDATA, posicion, (LPARAM)IndiceV);
            IndiceV = IndiceV->Siguiente;
        }

        SendMessage(GetDlgItem(hWnd, IDC_LIST3), LB_RESETCONTENT, 0, 0);
        Persona* IndiceP = OrigenP;
        while (IndiceP != NULL)
        {
            int array2[100];
            bool ciclo2 = false;
            char conf2[100];
            int numerob = 0;
            //strcpy_s(conf2, 100, OrigenP->Siguiente->APaterno);
            while (IndiceP != NULL && ciclo2 == false)
            {

                array2[numerob] = IndiceP->APaterno[0];

                if (strcmp(conf2, IndiceP->APaterno) == 0)
                {
                    ciclo2 = true;
                }
                numerob++;
                IndiceP = IndiceP->Siguiente;

            }

            quicksort(array2, 0, numerob - 1);
            IndiceP = OrigenP;
            for (int i = numerob - 1; i >= 0; i = i)
            {
                char letra2 = array2[i];


                if (letra2 == IndiceP->APaterno[0])
                {
                    wstring wAPaterno = s2ws(IndiceP->APaterno).append(L" ").append(s2ws(IndiceP->Nombres));
                    int posicion = SendMessage(GetDlgItem(hWnd, IDC_LIST3), LB_INSERTSTRING, 0, (LPARAM)wAPaterno.c_str());
                    SendMessage(GetDlgItem(hWnd, IDC_LIST3), LB_SETITEMDATA, posicion, (LPARAM)IndiceP);
                    i--;
                }
                IndiceP = IndiceP->Siguiente;
                if (IndiceP == NULL)
                {
                    IndiceP = OrigenP;
                }
            }
        }
        
        
        return (BOOL)TRUE;
    }break;
    case WM_COMMAND:
    {
        long wmId = LOWORD(wParam);
        if (MenuOpciones(hWnd, wmId))
        {
            return (BOOL)FALSE;
        }
        switch (wmId)
        {
        /*case IDC_LIST1:
        {
            int notificacion = HIWORD(wParam);
            switch (notificacion)
            {
            case LBN_SELCHANGE:
            {
                int Seleccion = SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_GETCURSEL, 0, 0);
                if (Seleccion >= 0)
                {
                    Carnet* Seleccionado=(Carnet*)SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_GETITEMDATA, Seleccion, 0);
                    DialogBox(hInst, s2ws(to_string(Seleccionado->ID)).c_str(), 0, 0);
                    //MessageBox(hWnd, s2ws(to_string(Seleccionado->ID)).c_str() , L"", 0);
                   //SetDlgItemText(hWnd, IDC_STATIC1, s2ws(to_string(Seleccionado->ID)).c_str());
                    Productos* Seleccionado = (Productos*)SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_GETITEMDATA, Seleccion, 0);
                    SetDlgItemText(hWnd, IDC_EDIT1, s2ws(Seleccionado->NombrePro).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT2, s2ws(Seleccionado->Marca).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT3, s2ws(to_string(Seleccionado->Codigo)).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT4, s2ws(Seleccionado->Descripcion).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT5, s2ws(to_string(Seleccionado->Monto)).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT6, s2ws(to_string(Seleccionado->Cantidad)).c_str());
                }
            }break;
            default:return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }*/
        default: return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
        EndPaint(hWnd, &ps);
    }break;
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }break;
    default: return (BOOL)FALSE;
    }

    return (BOOL)FALSE;
}
//Ventana de Modificacion de persona
BOOL CALLBACK Callback_Dialog11(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
    {
        return (BOOL)TRUE;
    }break;
    case WM_COMMAND:
    {
        long wmId = LOWORD(wParam);
        if (MenuOpciones(hWnd, wmId))
        {
            return (BOOL)FALSE;
        }
        switch (wmId)
        {
        case IDC_BUTTON1:
        {
            TCHAR buffer2[255];
            TCHAR buffer[255];

            GetDlgItemText(hWnd, IDC_EDIT1, buffer2, 255);
            wstring wBPer(buffer2);
            string BPer(wBPer.begin(), wBPer.end());

            if (BuscarPersona(BPer) != NULL)
            {
                SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_RESETCONTENT, 0, 0);
                Persona* IndiceP = OrigenP;
                while (IndiceP->APaterno != NULL)
                {

                    if (IndiceP->APaterno != BPer)
                    {
                        IndiceP = IndiceP->Siguiente;
                    }
                    else if (IndiceP->APaterno == BPer)
                    {
                        wstring wBPer = s2ws(IndiceP->APaterno).append(L" ").append(s2ws(IndiceP->AMaterno)).append(L" ").append(s2ws(IndiceP->Nombres));
                        //SendDlgItemMessage(hWnd, IDC_IMAGEN1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)IndiceP->DIdent);
                        int posicion = SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_INSERTSTRING, 0, (LPARAM)wBPer.c_str());
                        SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_SETITEMDATA, posicion, (LPARAM)IndiceP);
                        IndiceP = IndiceP->Siguiente;
                    }
                }
            }
            else
            {
                MessageBox(hWnd, L"La persina no se encontro o no existe Σ(っ °Д °;)っ", L"Error", 0);
            }

        }break;
        case IDC_BUTTON2:
        {
            TCHAR buffer3[255];
            TCHAR buffer4[255];
            TCHAR buffer5[255];
            TCHAR buffer[255];
            SYSTEMTIME Date;

            GetDlgItemText(hWnd, IDC_EDIT5, buffer3, 255);
            wstring wCURP(buffer3);
            string CURP(wCURP.begin(), wCURP.end());
            GetDlgItemText(hWnd, IDC_EDIT6, buffer4, 255);
            wstring wRFC(buffer4);
            string RFC(wRFC.begin(), wRFC.end());

            if (ValidacionCURPEspacios(hWnd, CURP) != NULL)
            {
                if (ValidacionRFCEspacios(hWnd, RFC) != NULL)
                {
                    DateTime_GetSystemtime(GetDlgItem(hWnd, IDC_DATETIMEPICKER1), &Date);
                    GetDateFormat(LOCALE_USER_DEFAULT, DATE_SHORTDATE, &Date, NULL, buffer, 255);

                    GetDlgItemText(hWnd, IDC_EDIT2, buffer, 255);
                    wstring wNombre(buffer);
                    GetDlgItemText(hWnd, IDC_EDIT4, buffer, 255);
                    wstring waMaterno(buffer);
                    GetDlgItemText(hWnd, IDC_EDIT3, buffer, 255);
                    wstring wAPaterno(buffer);
                    GetDlgItemText(hWnd, IDC_EDIT5, buffer, 255);
                    wstring wCURP(buffer);
                    GetDlgItemText(hWnd, IDC_EDIT6, buffer, 255);
                    wstring wRFC(buffer);
                    GetDlgItemText(hWnd, IDC_EDIT8, buffer, 255);
                    wstring wCalle(buffer);
                    GetDlgItemText(hWnd, IDC_EDIT9, buffer, 255);
                    wstring wColonia(buffer);
                    GetDlgItemText(hWnd, IDC_EDIT10, buffer, 255);
                    wstring wCuiudad(buffer);
                    GetDlgItemText(hWnd, IDC_EDIT11, buffer, 255);
                    wstring wEstado(buffer);
                    GetDlgItemText(hWnd, IDC_EDIT12, buffer, 255);
                    wstring wECivil(buffer);
                    GetDlgItemText(hWnd, IDC_EDIT13, buffer5, 255);
                    int Telefono = _wtoi(buffer5);
                    GetDlgItemText(hWnd, IDC_IMAGEN1, buffer, 255);
                    wstring wDIdent(buffer);
                    GetDlgItemText(hWnd, IDC_EDIT15, buffer, 255);
                    wstring wSexo(buffer);
                    GetDlgItemText(hWnd, IDC_EDIT16, buffer, 255);
                    wstring wGOcu(buffer);
                    GetDlgItemText(hWnd, IDC_EDIT17, buffer, 255);
                    wstring wFechaN(buffer);
                    wstring wPRiesgo(buffer);
                    string aMaterno(waMaterno.begin(), waMaterno.end());
                    string Nombre(wNombre.begin(), wNombre.end());
                    string CURP(wCURP.begin(), wCURP.end());
                    string RFC(wRFC.begin(), wRFC.end());
                    string Calle(wCalle.begin(), wCalle.end());
                    string Colonia(wColonia.begin(), wColonia.end());
                    string Cuiudad(wCuiudad.begin(), wCuiudad.end());
                    string APaterno(wAPaterno.begin(), wAPaterno.end());
                    string Estado(wEstado.begin(), wEstado.end());
                    string ECivil(wECivil.begin(), wECivil.end());
                    string DIdent(wDIdent.begin(), wDIdent.end());
                    string Sexo(wSexo.begin(), wSexo.end());
                    string GOcu(wGOcu.begin(), wGOcu.end());
                    string PRiesgo(wPRiesgo.begin(), wPRiesgo.end());
                    string FechaN(wFechaN.begin(), wFechaN.end());
                    ModidficarPersona(APaterno, APaterno, aMaterno, Nombre, CURP, RFC, FechaN, Calle, Colonia, Cuiudad, Estado, ECivil, Telefono, DIdent, Sexo, GOcu, PRiesgo);
                }
            }
            

            GetDlgItemText(hWnd, IDC_EDIT9, buffer, 255);
            SendMessage(GetDlgItem(hWnd, IDC_LIST3), LB_ADDSTRING, 0, (LPARAM)buffer);
        }break;
        case IDC_BUTTON3:
        {
            OPENFILENAME ofn;
            WCHAR FileName[1000] = { 0 };
            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(OPENFILENAME);
            ofn.hwndOwner = hWnd;
            ofn.lpstrFile = FileName;
            ofn.nMaxFile = 1000;
            ofn.lpstrFilter = L"Imagen BMP\0*.bmp\0";
            ofn.nFilterIndex = 1;
            ofn.lpstrTitle = NULL;
            ofn.nMaxFileTitle = 0;
            ofn.lpstrInitialDir = NULL;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            if (GetOpenFileName(&ofn) == TRUE)
            {
                HBITMAP imagen;
                imagen = (HBITMAP)LoadImage(hInst, FileName, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE | LR_DEFAULTCOLOR | LR_DEFAULTSIZE);
                if (imagen == NULL)
                {
                    MessageBox(hWnd, L"Error: No se pudo abrir la imagen", L"Image error", 0);
                }
                else
                {
                    SendDlgItemMessage(hWnd, IDC_IMAGEN1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }
            }
        }break;
        case IDC_LIST1:
        {
            long Notificacion = HIWORD(wParam);
            switch (Notificacion)
            {
            case LBN_SELCHANGE:
            {
                int Seleccion = SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_GETCURSEL, 0, 0);
                if (Seleccion >= 0)
                {
                    Persona* Seleccionado = (Persona*)SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_GETITEMDATA, Seleccion, 0);
                    SetDlgItemText(hWnd, IDC_EDIT2, s2ws(Seleccionado->Nombres).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT3, s2ws(Seleccionado->APaterno).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT4, s2ws(Seleccionado->AMaterno).c_str());
                    SetDlgItemText(hWnd, IDC_DATETIMEPICKER1, s2ws(Seleccionado->FechaN).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT5, s2ws(Seleccionado->CURP).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT6, s2ws(Seleccionado->RFC).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT8, s2ws(Seleccionado->Calle).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT9, s2ws(Seleccionado->Colonia).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT10, s2ws(Seleccionado->Cuidad).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT11, s2ws(Seleccionado->Estado).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT12, s2ws(Seleccionado->ECivil).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT13, s2ws(to_string(Seleccionado->Telefono)).c_str());
                    SetDlgItemText(hWnd, IDC_IMAGEN1, s2ws(Seleccionado->DIdent).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT15, s2ws(Seleccionado->Sexo).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT16, s2ws(Seleccionado->GOcupacional).c_str());
                    SetDlgItemText(hWnd, IDC_EDIT17, s2ws(Seleccionado->PRiesgp).c_str());


                }
            }break;
            default:return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }break;
        default: return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
        EndPaint(hWnd, &ps);
    }break;
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }break;
    default: return (BOOL)FALSE;
    }

    return (BOOL)FALSE;
}
//Ventana Borrar Vacuna
BOOL CALLBACK Callback_Dialog12(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
    {
        return (BOOL)TRUE;
    }break;
    case WM_COMMAND:
    {
        long wmId = LOWORD(wParam);
        if (MenuOpciones(hWnd, wmId))
        {
            return (BOOL)FALSE;
        }
        switch (wmId)
        {
        case IDC_BUTTON1:
        {
            TCHAR buffer2[255];
            TCHAR buffer[255];

            GetDlgItemText(hWnd, IDC_EDIT1, buffer2, 255);
            wstring wBVac(buffer2);
            string BVac(wBVac.begin(), wBVac.end());

            if (BuscarVacuna(BVac) != NULL)
            {
                SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_RESETCONTENT, 0, 0);
                Vacuna* IndiceV = OrigenV;
                while (IndiceV->ClaveV != BVac)
                {
                    IndiceV = IndiceV->Siguiente;
                }
                if (IndiceV->ClaveV == BVac)
                {
                    wstring wNombrePro = s2ws(IndiceV->ClaveV).append(L" - ").append(s2ws(IndiceV->Marca));
                    int posicion = SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_INSERTSTRING, 0, (LPARAM)wBVac.c_str());
                    SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_SETITEMDATA, posicion, (LPARAM)IndiceV);
                }
            }
            else
            {
                MessageBox(hWnd, L"La vacuna no se encontro o no esta registrada", L"Error", 0);
            }
        }break;
        case IDC_BUTTON2:
        {
            TCHAR buffer2[255];
            GetDlgItemText(hWnd, IDC_EDIT1, buffer2, 255);
            wstring wBvac(buffer2);
            string Bvac(wBvac.begin(), wBvac.end());
            BorrarVacunaEnMedioSec(Bvac);

            int Seleccion = SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_GETCURSEL, 0, 0);
            if (Seleccion >= 0)
            {
                SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_DELETESTRING, Seleccion, 0);
            }
        }break;
        default: return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
        EndPaint(hWnd, &ps);
    }break;
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }break;
    default: return (BOOL)FALSE;
    }

    return (BOOL)FALSE;
}
//Ventana de Borrar Perosna
BOOL CALLBACK Callback_Dialog13(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
    {
        return (BOOL)TRUE;
    }break;
    case WM_COMMAND:
    {
        long wmId = LOWORD(wParam);
        if (MenuOpciones(hWnd, wmId))
        {
            return (BOOL)FALSE;
        }
        switch (wmId)
        {
        case IDC_BUTTON1:
        {
            TCHAR buffer2[255];
            TCHAR buffer[255];

            GetDlgItemText(hWnd, IDC_EDIT1, buffer2, 255);
            wstring wBPer(buffer2);
            string BPer(wBPer.begin(), wBPer.end());

            if (BuscarPersona(BPer) != NULL)
            {
                SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_RESETCONTENT, 0, 0);
                Persona* IndiceP = OrigenP;
                while (IndiceP->APaterno != NULL)
                {

                    if (IndiceP->APaterno != BPer)
                    {
                        IndiceP = IndiceP->Siguiente;
                    }
                    else if (IndiceP->APaterno == BPer)
                    {
                        wstring wBPer = s2ws(IndiceP->APaterno).append(L" ").append(s2ws(IndiceP->AMaterno)).append(L" ").append(s2ws(IndiceP->Nombres));
                        int posicion = SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_INSERTSTRING, 0, (LPARAM)wBPer.c_str());
                        SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_SETITEMDATA, posicion, (LPARAM)IndiceP);
                        IndiceP = IndiceP->Siguiente;
                    }
                }
            }
            else
            {
                MessageBox(hWnd, L"La persina no se encontro o no existe Σ(っ °Д °;)っ", L"Error", 0);
            }
        }break;
        case IDC_BUTTON2:
        {
            TCHAR buffer2[255];
            GetDlgItemText(hWnd, IDC_EDIT1, buffer2, 255);
            wstring wBper(buffer2);
            string Bper(wBper.begin(), wBper.end());
            BorrarPersonaEnMedioSec(Bper);

            int Seleccion = SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_GETCURSEL, 0, 0);
            if (Seleccion >= 0)
            {
                SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_DELETESTRING, Seleccion, 0);
            }
        }break;
        default: return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
        EndPaint(hWnd, &ps);
    }break;
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }break;
    default: return (BOOL)FALSE;
    }

    return (BOOL)FALSE;
}

//Funciones
//Funciones y estructuras de usuario(lata, mod, baja, buscar)

void AgregarUsuarioAlInicio(Usuario* User)
{
    if (OrigenU == NULL)
    {
        OrigenU = User;
    }
    else
    {
        Usuario* Indice = OrigenU;
        User->Siguiente = Indice;
        Indice->Anterior = User;
        OrigenU = User;
    }
}
Usuario* AltaUser(string ClaveUs, string Contrasena, string APaterno, string AMaterno, string Nombre)
{
    Usuario* User = new Usuario;
    strcpy_s(User->ClaveUs, 200, ClaveUs.c_str());
    strcpy_s(User->Contrasena, 200, Contrasena.c_str());
    strcpy_s(User->APaterno, 200, APaterno.c_str());
    strcpy_s(User->AMaterno, 200, AMaterno.c_str());
    strcpy_s(User->Nombres, 200, Nombre.c_str());
    User->Anterior = NULL;
    User->Siguiente = NULL;

    return User;
}
Usuario* ValidacionContrasena(string BuscarContrasena)
{
    if (OrigenU == NULL)
    {
        return NULL;
    }
    Usuario* IndiceU = OrigenU;
    bool ContrasenaEncontrado = false;
    while (IndiceU != NULL)
    {
        if (_strcmpi(IndiceU->Contrasena, BuscarContrasena.c_str()) == 0)
        {

            ContrasenaEncontrado = true;
            break;

        }
        IndiceU = IndiceU->Siguiente;
    }
    return IndiceU;
}
Usuario* ValidacionUsuario(string BuscarUsuario)
{
    if (OrigenU == NULL)
    {
        return NULL;
    }
    Usuario* IndiceU = OrigenU;
    bool ContrasenaEncontrado = false;
    while (IndiceU != NULL)
    {
        if (_strcmpi(IndiceU->ClaveUs, BuscarUsuario.c_str()) == 0)
        {
            ContrasenaEncontrado = true;
            break;

        }
        IndiceU = IndiceU->Siguiente;
    }
    return IndiceU;
}
//Funciones y estructuras de Carnet
void AgragarCarnetAlInicio(Carnet* carnet)
{
    if (OrigenC == NULL)
    {
        OrigenC = carnet;
    }
    else
    {
        Carnet* IndiceC = OrigenC;
        carnet->Siguiente = IndiceC;
        IndiceC->Anterior = carnet;
        OrigenC = carnet;
    }
}
Carnet* AltaCarnet(string CURP, string Vacuna, string Dosis, string FechaD, string Lote, string CVacunacion,string NombreC, int ID)
{
    Carnet* carnet = new Carnet;
    strcpy_s(carnet->CURP, 200, CURP.c_str());
    strcpy_s(carnet->Vacuna, 200, Vacuna.c_str());
    strcpy_s(carnet->Dosis, 200, Dosis.c_str());
    strcpy_s(carnet->FechaD, 200, FechaD.c_str());
    strcpy_s(carnet->Lote, 200, Lote.c_str());
    strcpy_s(carnet->CVacunacion, 200, CVacunacion.c_str());
    strcpy_s(carnet->Nombre, 200, NombreC.c_str());
    carnet->ID = ID;
    carnet->Siguiente = NULL;

    return carnet;
}
void ModificarCarnet(string NombreCarnetBuscar, string CURP, string vacuna, string Dosis, string FechaD, string Lote, string CVacunacion)
{
    if (OrigenC == NULL)
    {
        return;
    }
    Carnet* IndiceC = BuscarCarnet(NombreCarnetBuscar);
    if (IndiceC != NULL)
    {
        strcpy_s(IndiceC->CURP, 200, CURP.c_str());
        strcpy_s(IndiceC->Vacuna, 200, vacuna.c_str());
        strcpy_s(IndiceC->Dosis, 200, Dosis.c_str());
        strcpy_s(IndiceC->FechaD, 200, FechaD.c_str());
        strcpy_s(IndiceC->Lote, 200, Lote.c_str());
        strcpy_s(IndiceC->CVacunacion, 200, CVacunacion.c_str());
    }
}
Carnet* BuscarCarnet(string BuscarCarnet)
{
    if (OrigenC == NULL)
    {
        return NULL;
    }
    Carnet* IndiceC = OrigenC;
    bool CarnetEncontrado = false;
    while (IndiceC != NULL)
    {
        if (_strcmpi(IndiceC->Nombre, BuscarCarnet.c_str()) == 0)
        {
            CarnetEncontrado = true;
            break;

        }
        IndiceC = IndiceC->Siguiente;
    }
    return IndiceC;
}
Carnet* BuscarCarnetValid(int BuscarCarnetID)
{
    if (OrigenC == NULL)
    {
        return NULL;
    }
    Carnet* IndiceC = OrigenC;
    bool CarnetEncontrado = false;
    while (IndiceC != NULL)
    {
        if (IndiceC->ID == BuscarCarnetID)
        {
            CarnetEncontrado = true;
            break;

        }
        IndiceC = IndiceC->Siguiente;
    }
    return IndiceC;
}
Carnet* BuscarCarnetBin(HWND hWnd, int BuscarCarnetBin)//Incompleta
{
    int Inf = 0;
    int Sup = 0;
    int Mid;
    int X[20];

    if (OrigenC == NULL)
    {
        return NULL;
    }
    Carnet* IndiceC = OrigenC;
    Carnet* Anterior = IndiceC->Anterior;
    Carnet* Siguiente = IndiceC->Siguiente;
    bool CarnetEncontrado = false;
    
    while (IndiceC != NULL)
    {
        Sup++;
        IndiceC = IndiceC->Siguiente;
    }
    for (int i = 0; i <= Sup; i++)
    {
        IndiceC = Siguiente;
    }
   
    for (int i = 0; i < Sup; i++)
    {
        X[i] = IndiceC->ID;
        IndiceC = Siguiente;
    }
    while (IndiceC != NULL)
    {
        while (Inf <= Sup)
        {
            Mid = (Inf + Sup) / 2;

            if (X[Mid] = BuscarCarnetBin)
            {
                CarnetEncontrado = true;
                break;
            }
            if (X[Mid] > BuscarCarnetBin)
            {
                Sup = Mid;
                Mid = (Inf + Sup) / 2;
            }
            if (X[Mid] < BuscarCarnetBin)
            {
                Inf = Mid;
                Mid = (Inf + Sup) / 2;
            }
        }
        if (CarnetEncontrado == true)
        {
            return IndiceC;
        }
        else
        {
            MessageBox(hWnd, L"No se encontro el carnet", L"Advertencia", 0);
        }
    }
    
}
Carnet* BuscarCarnetsec(string BuscarCarnet)
{
    if (OrigenC == NULL)
    {
        return NULL;
    }
    Carnet* IndiceC = OrigenC;
    bool CarnetEncontrado = false;
    while (IndiceC != NULL)
    {
        if (_strcmpi(IndiceC->Nombre, BuscarCarnet.c_str()) == 0)
        {
            CarnetEncontrado = true;
            break;

        }
        IndiceC = IndiceC->Siguiente;
    }
    return IndiceC;
}
//falta buscar acarnet binario
void BorrarCarnetEnMedioSec(string NombreCarnetBuscar)
{
    if (OrigenC == NULL)
    {
        return;
    }
    Carnet* IndiceC = BuscarCarnetsec(NombreCarnetBuscar);
    if (IndiceC != NULL)
    {
        Carnet* Anterior = IndiceC->Anterior;
        Carnet* Siguiente = IndiceC->Siguiente;
        if (Anterior == NULL)
        {
            BorrarCarnetAlInicio();
        }
        else if (Siguiente == NULL)
        {
            BorrarCarnetAlFinal();
        }
        else
        {
            Anterior->Siguiente = Siguiente;
            Siguiente->Anterior = Anterior;
            delete IndiceC;
        }

    }
}
void BorrarCarnetAlInicio()
{
    if (OrigenC == NULL)
    {
        return;
    }
    Carnet* IndiceC = OrigenC;
    OrigenC = OrigenC->Siguiente;
    if (OrigenC != NULL)
    {
        OrigenC->Anterior = NULL;
    }
    delete IndiceC;
}
void BorrarCarnetAlFinal()
{
    if (OrigenC == NULL)
    {
        return;
    }
    Carnet* IndiceC = OrigenC;
    while (IndiceC->Siguiente != NULL)
    {
        IndiceC = IndiceC->Siguiente;
    }
    Carnet* Anterior = IndiceC->Anterior;
    if (Anterior != NULL)
    {
        Anterior->Siguiente = NULL;
    }
    delete IndiceC;
}
//funciones y estructuras de Vacuna
void AgregarVacunasAlInicio(Vacuna* vacuna)
{
    if (OrigenV == NULL)
    {
        OrigenV = vacuna;
    }
    else
    {
        Vacuna* IndiceV = OrigenV;
        vacuna->Siguiente = IndiceV;
        IndiceV->Anterior = vacuna;
        OrigenV = vacuna;
    }
}
Vacuna* AltaVacuna(string Tipo, string Marca, int NoDosis, string ClaveV, string Descrip, float Precio)
{
    Vacuna* vacuna = new Vacuna;
    strcpy_s(vacuna->tipo, 200, Tipo.c_str());
    strcpy_s(vacuna->Marca, 200, Marca.c_str());
    vacuna->NoDosis = NoDosis;
    strcpy_s(vacuna->ClaveV, 200, ClaveV.c_str());
    strcpy_s(vacuna->Descrip, 1000, Tipo.c_str());
    vacuna->Precio = Precio;
    vacuna->Anterior = NULL;
    vacuna->Siguiente = NULL;

    return vacuna;
}
void ModificarVacuna(string NombreVacunaBuscar, string Tipo, string Marca, int NoMarca, string ClaveV, string Descrip, float Precio)
{
    if (OrigenC == NULL)
    {
        return;
    }
    Vacuna* IndiceV = BuscarVacuna(NombreVacunaBuscar);
    if (IndiceV != NULL)
    {
        strcpy_s(IndiceV->tipo, 200, Tipo.c_str());
        strcpy_s(IndiceV->Marca, 200, Marca.c_str());
        IndiceV->NoDosis = NoMarca;
        strcpy_s(IndiceV->ClaveV, 200, ClaveV.c_str());
        strcpy_s(IndiceV->Descrip, 200, Descrip.c_str());
        IndiceV->Precio = Precio;
        
    }
}
Vacuna* BuscarVacuna(string BuscarVacuna)
{
    if (OrigenV == NULL)
    {
        return NULL;
    }
    Vacuna* IndiceV = OrigenV;
    bool VacunaEncontrado = false;
    while (IndiceV != NULL)
    {
        if (_strcmpi(IndiceV->ClaveV, BuscarVacuna.c_str()) == 0)
        {
            VacunaEncontrado = true;
            break;

        }
        IndiceV = IndiceV->Siguiente;
    }
    return IndiceV;
}
void BorrarVacunaEnMedioSec(string NombreVacunaBuscar)
{
    if (OrigenV == NULL)
    {
        return;
    }
    Vacuna* IndiceV = BuscarVacuna(NombreVacunaBuscar);
    if (IndiceV != NULL)
    {
        Vacuna* Anterior = IndiceV->Anterior;
        Vacuna* Siguiente = IndiceV->Siguiente;
        if (Anterior == NULL)
        {
            BorrarVacunaAlInicio();
        }
        else if (Siguiente == NULL)
        {
            BorrarVacunaAlFinal();
        }
        else
        {
            Anterior->Siguiente = Siguiente;
            Siguiente->Anterior = Anterior;
            delete IndiceV;
        }

    }
}
void BorrarVacunaAlInicio()
{
    if (OrigenV == NULL)
    {
        return;
    }
    Vacuna* IndiceV = OrigenV;
    OrigenV = OrigenV->Siguiente;
    if (OrigenV != NULL)
    {
        OrigenV->Anterior = NULL;
    }
    delete IndiceV;
}
void BorrarVacunaAlFinal()
{
    if (OrigenV == NULL)
    {
        return;
    }
    Vacuna* IndiceV = OrigenV;
    while (IndiceV->Siguiente != NULL)
    {
        IndiceV = IndiceV->Siguiente;
    }
    Vacuna* Anterior = IndiceV->Anterior;
    if (Anterior != NULL)
    {
        Anterior->Siguiente = NULL;
    }
    delete IndiceV;
}
Vacuna* ValidacionClaveVacuna(string BuscarClave)
{
    if (OrigenV == NULL)
    {
        return NULL;
    }
    Vacuna* IndiceV = OrigenV;
    bool ClaveEncontrado = false;
    while (IndiceV != NULL)
    {
        if (_strcmpi(IndiceV->ClaveV, BuscarClave.c_str()) == 0)
        {
            return NULL;
            break;

        }
        IndiceV = IndiceV->Siguiente;
    }
    return IndiceV;
}
//funciones y estructuras de persona
void AgregarPersonaAlInicio(Persona* persona)
{
    if (OrigenP == NULL)
    {
        OrigenP = persona;
    }
    else
    {
        Persona* IndiceP = OrigenP;
        persona->Siguiente = IndiceP;
        IndiceP->Anterior = persona;
        OrigenP = persona;
    }
}
Persona* AltaPersona(string APaterno, string AMaterno, string Nombre, string CURP, string RFC, string FechaN, string Calle, string Colonia, string Ciudad, string Estado, string ECivil, int Telefono, string DInt, string Sexo, string GOcupacional, string PRiesgo)
{
    Persona* persona = new Persona;
    strcpy_s(persona->APaterno, 200, APaterno.c_str());
    strcpy_s(persona->AMaterno, 200, AMaterno.c_str());
    strcpy_s(persona->Nombres, 200, Nombre.c_str());
    strcpy_s(persona->CURP, 200, CURP.c_str());
    strcpy_s(persona->RFC, 200, RFC.c_str());
    strcpy_s(persona->FechaN, 200, FechaN.c_str());
    strcpy_s(persona->Calle, 200, Calle.c_str());
    strcpy_s(persona->Colonia, 200, Colonia.c_str());
    strcpy_s(persona->Cuidad, 200, Ciudad.c_str());
    strcpy_s(persona->Estado, 200, Estado.c_str());
    strcpy_s(persona->ECivil, 200, ECivil.c_str());
    persona->Telefono = Telefono;
    strcpy_s(persona->DIdent, 200, DInt.c_str());
    strcpy_s(persona->Sexo, 200, Sexo.c_str());
    strcpy_s(persona->GOcupacional, 200, GOcupacional.c_str());
    strcpy_s(persona->PRiesgp, 200, PRiesgo.c_str());
    persona->Anterior = NULL;
    persona->Siguiente = NULL;

    return persona;
}
void ModidficarPersona(string NombrePersonaBuscar, string APaterno, string AMaterno, string Nombre, string CURP, string RFC, string FechaN, string Calle, string Colonia, string Ciudad, string Estado, string ECivil, int Telefono, string DInt, string Sexo, string GOcupacional, string PRiesgo)
{
    if (OrigenP == NULL)
    {
        return;
    }
    Persona* IndiceP = BuscarPersona(NombrePersonaBuscar);
    if (IndiceP != NULL)
    {
        strcpy_s(IndiceP->APaterno, 200, APaterno.c_str());
        strcpy_s(IndiceP->AMaterno, 200, AMaterno.c_str());
        strcpy_s(IndiceP->Nombres, 200, Nombre.c_str());
        strcpy_s(IndiceP->CURP, 200, CURP.c_str());
        strcpy_s(IndiceP->RFC, 200, RFC.c_str());
        strcpy_s(IndiceP->FechaN, 200, FechaN.c_str());
        strcpy_s(IndiceP->Calle, 200, Calle.c_str());
        strcpy_s(IndiceP->Colonia, 200, Colonia.c_str());
        strcpy_s(IndiceP->Cuidad, 200, Ciudad.c_str());
        strcpy_s(IndiceP->Estado, 200, Estado.c_str());
        strcpy_s(IndiceP->ECivil, 200, ECivil.c_str());
        IndiceP->Telefono = Telefono;
        strcpy_s(IndiceP->DIdent, 200, DInt.c_str());
        strcpy_s(IndiceP->Sexo, 200, Sexo.c_str());
        strcpy_s(IndiceP->GOcupacional, 200, GOcupacional.c_str());
        strcpy_s(IndiceP->PRiesgp, 200, PRiesgo.c_str());

    }
}
Persona* BuscarPersona(string BuscarPersona)
{
    if (OrigenP == NULL)
    {
        return NULL;
    }
    Persona* IndiceP = OrigenP;
    bool PersonaEncontrado = false;
    while (IndiceP != NULL)
    {
        if (_strcmpi(IndiceP->APaterno, BuscarPersona.c_str()) == 0)
        {
            PersonaEncontrado = true;
            break;

        }
        IndiceP = IndiceP->Siguiente;
    }
    return IndiceP;
}
void BorrarPersonaEnMedioSec(string NombrePersonaBuscar)
{
    if (OrigenP == NULL)
    {
        return;
    }
    Persona* IndiceP = BuscarPersona(NombrePersonaBuscar);
    if (IndiceP != NULL)
    {
        Persona* Anterior = IndiceP->Anterior;
        Persona* Siguiente = IndiceP->Siguiente;
        if (Anterior == NULL)
        {
            BorrarPersonaAlInicio();
        }
        else if (Siguiente == NULL)
        {
            BorrarPersonaAlFinal();
        }
        else
        {
            Anterior->Siguiente = Siguiente;
            Siguiente->Anterior = Anterior;
            delete IndiceP;
        }

    }
}
void BorrarPersonaAlInicio()
{
    if (OrigenP == NULL)
    {
        return;
    }
    Persona* IndiceP = OrigenP;
    OrigenP = OrigenP->Siguiente;
    if (OrigenP != NULL)
    {
        OrigenP->Anterior = NULL;
    }
    delete IndiceP;
}
void BorrarPersonaAlFinal()
{
    if (OrigenP == NULL)
    {
        return;
    }
    Persona* IndiceP = OrigenP;
    while (IndiceP->Siguiente != NULL)
    {
        IndiceP = IndiceP->Siguiente;
    }
    Persona* Anterior = IndiceP->Anterior;
    if (Anterior != NULL)
    {
        Anterior->Siguiente = NULL;
    }
    delete IndiceP;
}
Persona* ValidacionCURP(string BuscarCURP)
{
    if (OrigenP == NULL)
    {
        return NULL;
    }
    Persona* IndiceP = OrigenP;
    bool CURPEncontrado = false;
    while (IndiceP != NULL)
    {
        if (_strcmpi(IndiceP->CURP, BuscarCURP.c_str()) == 0)
        {
            //MessageBox(hWnd, L"CURP ya existente ", L"Error", 0);
            return NULL;
            break;
            //CURPEncontrado = true;s

        }
        /*else
        {
            return IndiceP;
        }*/
        IndiceP = IndiceP->Siguiente;
    }
    return IndiceP;
}
Persona* ValidacionRFC(string BuscarRFC)
{
    if (OrigenP == NULL)
    {
        return NULL;
    }
    Persona* IndiceP = OrigenP;
    bool RFCEncontrado = false;
    while (IndiceP != NULL)
    {
        if (_strcmpi(IndiceP->RFC, BuscarRFC.c_str()) == 0)
        {
            return NULL;
            break;

        }
        else
        {
            return IndiceP;
        }
        IndiceP = IndiceP->Siguiente;
    }
    return IndiceP;
}
Persona* ValidacionCURPInicial(string BuscarCURP)
{
    if (OrigenP == NULL)
    {
        return NULL;
    }
    Persona* IndiceP = OrigenP;
   /* while (IndiceP != NULL)
    {
        if (_strcmpi(IndiceP->CURP, BuscarCURP.c_str()) == 0)
        {
            //MessageBox(hWnd, L"CURP ya existente ", L"Error", 0);
            return NULL;
            break;
            //CURPEncontrado = true;s

        }
        IndiceP = IndiceP->Siguiente;
    }*/
    return IndiceP;
}
Persona* ValidacionCURPEspacios(HWND hWnd, string BuscarCURP)
{
    if (OrigenP == NULL)
    {
        return NULL;
    }
    Persona* IndiceP = OrigenP;
    for (int i = 0; i <= strlen(BuscarCURP.c_str()); ++i)
    {
        if (isspace(BuscarCURP[i]))
        {
            MessageBox(hWnd, L"No se permiten espacion en blanco en CURP", L"ERROR", 0);
            return NULL;
            break;
        }

    }
    return IndiceP;
}
Persona* ValidacionRFCEspacios(HWND hWnd, string BuscarRFC)
{
    if (OrigenP == NULL)
    {
        return NULL;
    }
    Persona* IndiceP = OrigenP;
    for (int i = 0; i <= strlen(BuscarRFC.c_str()); ++i)
    {
        if (isspace(BuscarRFC[i]))
        {
            MessageBox(hWnd, L"No se permiten espacion en blanco en RFC", L"ERROR", 0);
            return NULL;
            break;
        }

    }
    return IndiceP;
}
// Funciones yy estructurascde archivos binarios (Alta, carga)
void GuardarArchivoUsuario()
{
    ofstream ArchU;
    ArchU.open("D:\\edgar\\Desktop\\1ra Entrega\\Usuarios.bin", ios::binary | ios::trunc);
    if (ArchU.is_open())
    {
        Usuario* Indice = OrigenU;
        while (Indice != NULL)
        {
            ArchU.write((char*)Indice, sizeof(Usuario));
            Indice = Indice->Siguiente;
        }
        ArchU.close();
    }
}
void GuardarArchivoCarnet()
{
    ofstream ArchC;
    ArchC.open("D:\\edgar\\Desktop\\1ra Entrega\\Carnet.bin", ios::binary | ios::trunc);
    if (ArchC.is_open())
    {
        Carnet* IndiceC = OrigenC;
        while (IndiceC != NULL)
        {
            ArchC.write((char*)IndiceC, sizeof(Carnet));
            IndiceC = IndiceC->Siguiente;
        }
        ArchC.close();
    }
}
void GuardarArchivoVacuna()
{
    ofstream ArchV;
    ArchV.open("D:\\edgar\\Desktop\\1ra Entrega\\Vacuna.bin", ios::binary | ios::trunc);
    if (ArchV.is_open())
    {
        Vacuna* IndiceV = OrigenV;
        while (IndiceV != NULL)
        {
            ArchV.write((char*)IndiceV, sizeof(Vacuna));
            IndiceV = IndiceV->Siguiente;
        }
        ArchV.close();
    }
}
void GuardarArchivoPersona()
{
    ofstream ArchP;
    ArchP.open("D:\\edgar\\Desktop\\1ra Entrega\\Persona.bin", ios::binary | ios::trunc);
    if (ArchP.is_open())
    {
        Persona* IndiceP = OrigenP;
        while (IndiceP != NULL)
        {
            ArchP.write((char*)IndiceP, sizeof(Persona));
            IndiceP = IndiceP->Siguiente;
        }
        ArchP.close();
    }
}

void LeerArchivoUsuario()
{
    ifstream ArchU;
    ArchU.open("D:\\edgar\\Desktop\\1ra Entrega\\Usuarios.bin", ios::binary | ios::in);
    if (ArchU.is_open())
    {
        ArchU.seekg(0, ArchU.end);
        int Bytesleidos = ArchU.tellg();
        ArchU.seekg(0, ArchU.beg);
        int Bytes = 0;
        while (Bytes < Bytesleidos)
        {
            Usuario* UserReed = new Usuario;
            ArchU.read(reinterpret_cast<char*>(UserReed), sizeof(Usuario));
            UserReed->Anterior = NULL;
            UserReed->Siguiente = NULL;
            AgregarUsuarioAlInicio(UserReed);
            Bytes = Bytes + sizeof(Usuario);
        }
        ArchU.close();
    }
}
void LeerArchivoCarnet()
{
    ifstream ArchC;
    ArchC.open("D:\\edgar\\Desktop\\1ra Entrega\\Carnet.bin", ios::binary | ios::in);
    if (ArchC.is_open())
    {
        ArchC.seekg(0, ArchC.end);
        int Bytesleidos = ArchC.tellg();
        ArchC.seekg(0, ArchC.beg);
        int Bytes = 0;
        while (Bytes < Bytesleidos)
        {
            Carnet* CarnetReed = new Carnet;
            ArchC.read(reinterpret_cast<char*>(CarnetReed), sizeof(Carnet));
            CarnetReed->Anterior = NULL;
            CarnetReed->Siguiente = NULL;
            AgragarCarnetAlInicio(CarnetReed);
            Bytes = Bytes + sizeof(Carnet);
        }
        ArchC.close();
    }
}
void LeerArchivoVacuna()
{
    ifstream ArchV;
    ArchV.open("D:\\edgar\\Desktop\\1ra Entrega\\Vacuna.bin", ios::binary | ios::in);
    if (ArchV.is_open())
    {
        ArchV.seekg(0, ArchV.end);
        int Bytesleidos = ArchV.tellg();
        ArchV.seekg(0, ArchV.beg);
        int Bytes = 0;
        while (Bytes < Bytesleidos)
        {
            Vacuna* VacunaReed = new Vacuna;
            ArchV.read(reinterpret_cast<char*>(VacunaReed), sizeof(Vacuna));
            VacunaReed->Anterior = NULL;
            VacunaReed->Siguiente = NULL;
            AgregarVacunasAlInicio(VacunaReed);
            Bytes = Bytes + sizeof(Vacuna);
        }
        ArchV.close();
    }
}
void LeerArchivoPersona()
{
    ifstream ArchP;
    ArchP.open("D:\\edgar\\Desktop\\1ra Entrega\\Persona.bin", ios::binary | ios::in);
    if (ArchP.is_open())
    {
        ArchP.seekg(0, ArchP.end);
        int Bytesleidos = ArchP.tellg();
        ArchP.seekg(0, ArchP.beg);
        int Bytes = 0;
        while (Bytes < Bytesleidos)
        {
            Persona* PersonaReed = new Persona;
            ArchP.read(reinterpret_cast<char*>(PersonaReed), sizeof(Persona));
            PersonaReed->Anterior = NULL;
            PersonaReed->Siguiente = NULL;
            AgregarPersonaAlInicio(PersonaReed);
            Bytes = Bytes + sizeof(Persona);
        }
        ArchP.close();
    }
}

std::wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

//Quicksort
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

//Heapsort
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

// FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
// PURPOSE: Processes messages for the main window.
//
// WM_COMMAND - process the application menu
// WM_PAINT - Paint the main window
// WM_DESTROY - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
       /* int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }*/
    }
    break;
    case WM_PAINT:
    {
        /*PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);*/
    }
    break;
    case WM_DESTROY:
       /* PostQuitMessage(0);*/
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}