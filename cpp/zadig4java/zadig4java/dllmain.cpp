// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <setupapi.h>
#include <shlobj_core.h>

#include "lt_terzer_Libwdi.h"
#include "misc.h"

using namespace std;

#define INF_NAME    "usb_device.inf"
#define DEFAULT_DIR "usb_driver"

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved)
{
    return TRUE;
}

JNIEXPORT jint JNICALL Java_lt_terzer_Libwdi_installDriver__II
(JNIEnv* env, jclass thisObject, jint vid, jint driverType)
{
    wdi_log_level(WDI_LOG_LEVEL_NONE);
    struct wdi_device_info* device, * list;
    int result = WDI_SUCCESS;
    result = wdi_create_list(&list, NULL);
    if (result == WDI_SUCCESS) {
        for (device = list; device != NULL; device = device->next) {
            if (device->vid == vid && device->driver == NULL) {
                wdi_options_prepare_driver opd = { 0 };
                opd.driver_type = driverType;
                wdi_options_install_driver oid = { 0 };
                result = wdi_prepare_driver(device, DEFAULT_DIR, INF_NAME, &opd);
                if (result == WDI_SUCCESS) {
                    result = wdi_install_driver(device, DEFAULT_DIR, INF_NAME, &oid);
                }
            }
        }
        wdi_destroy_list(list);
    }
    return result;
}

JNIEXPORT jint JNICALL Java_lt_terzer_Libwdi_installDriver__III
(JNIEnv* env, jclass thisObject, jint vid, jint pid, jint driverType)
{
    wdi_log_level(WDI_LOG_LEVEL_NONE);
    struct wdi_device_info* device, * list;
    int result = WDI_SUCCESS;
    result = wdi_create_list(&list, NULL);
    if (result == WDI_SUCCESS) {
        for (device = list; device != NULL; device = device->next) {
            if (device->vid == vid && device->pid == pid && device->driver == NULL) {
                wdi_options_prepare_driver opd = { 0 };
                opd.driver_type = driverType;
                wdi_options_install_driver oid = { 0 };
                result = wdi_prepare_driver(device, DEFAULT_DIR, INF_NAME, &opd);
                if (result == WDI_SUCCESS) {
                    result = wdi_install_driver(device, DEFAULT_DIR, INF_NAME, &oid);
                }
            }
        }
        wdi_destroy_list(list);
    }
    return result;
}