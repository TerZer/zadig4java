// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
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

JNIEXPORT jint JNICALL Java_lt_terzer_Libwdi__1installDriver__II
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

JNIEXPORT jint JNICALL Java_lt_terzer_Libwdi__1installDriver__III
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

vector<string> countDevicesWithoutDriver(int* vid, int* pid) {
    vector<string> devices;
    struct wdi_device_info* device, * list;
    int result = WDI_SUCCESS;
    result = wdi_create_list(&list, NULL);
    if (result == WDI_SUCCESS) {
        for (device = list; device != NULL; device = device->next) {
            if (device->driver == NULL) {
                if (vid != NULL && pid != NULL) {
                    if (device->vid == *vid && device->pid == *pid) {
                        devices.push_back(device->device_id);
                    }
                }
                else if (vid != NULL) {
                    if (device->vid == *vid) {
                        devices.push_back(device->device_id);
                    }
                }
                else if (pid != NULL) {
                    if (device->pid == *pid) {
                        devices.push_back(device->device_id);
                    }
                }
                else {
                    devices.push_back(device->device_id);
                }
            }
        }
        wdi_destroy_list(list);
    }
    return devices;
}

JNIEXPORT jboolean JNICALL Java_lt_terzer_Libwdi__1containsDeviceWithoutDriver__I
(JNIEnv* env, jclass thisObject, jint vid)
{
    int VID = vid;
    vector<string> devices = countDevicesWithoutDriver(&VID, NULL);
    return devices.size() > 0;
}

JNIEXPORT jboolean JNICALL Java_lt_terzer_Libwdi__1containsDeviceWithoutDriver__II
(JNIEnv* env, jclass thisObject, jint vid, jint pid)
{
    int VID = vid;
    int PID = pid;
    vector<string> devices = countDevicesWithoutDriver(&VID, &PID);
    return devices.size() > 0;
}

JNIEXPORT jobjectArray JNICALL Java_lt_terzer_Libwdi__1getDevicesWithoutDriver__
(JNIEnv* env, jclass thisObject)
{
    vector<string> devices = countDevicesWithoutDriver(NULL, NULL);
    jclass stringClass = env->FindClass("java/lang/String");
    jobjectArray array = env->NewObjectArray(devices.size(), stringClass, 0);
    for (int i = 0; i < devices.size(); i++) {
        jstring deviceId = env->NewStringUTF(devices[i].c_str());
        env->SetObjectArrayElement(array, i, deviceId);
    }
    return array;
}

JNIEXPORT jobjectArray JNICALL Java_lt_terzer_Libwdi__1getDevicesWithoutDriver__I
(JNIEnv* env, jclass thisObject, jint vid)
{
    int VID = vid;
    vector<string> devices = countDevicesWithoutDriver(&VID, NULL);
    jclass stringClass = env->FindClass("java/lang/String");
    jobjectArray array = env->NewObjectArray(devices.size(), stringClass, 0);
    for (int i = 0; i < devices.size(); i++) {
        jstring deviceId = env->NewStringUTF(devices[i].c_str());
        env->SetObjectArrayElement(array, i, deviceId);
    }
    return array;
}

JNIEXPORT jobjectArray JNICALL Java_lt_terzer_Libwdi__1getDevicesWithoutDriver__II
(JNIEnv* env, jclass thisObject, jint vid, jint pid)
{
    int VID = vid;
    int PID = pid;
    vector<string> devices = countDevicesWithoutDriver(&VID, &PID);
    jclass stringClass = env->FindClass("java/lang/String");
    jobjectArray array = env->NewObjectArray(devices.size(), stringClass, 0);
    for (int i = 0; i < devices.size(); i++) {
        jstring deviceId = env->NewStringUTF(devices[i].c_str());
        env->SetObjectArrayElement(array, i, deviceId);
    }
    return array;
}