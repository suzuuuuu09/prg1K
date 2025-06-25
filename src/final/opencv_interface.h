#ifndef OPENCV_INTERFACE_H
#define OPENCV_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

/* C++で実装されたOpenCV関数をCから呼び出す */
int video_get_resolution(void);
int display_image_wrapper(const char* image_path);

#ifdef __cplusplus
}
#endif

#endif /* OPENCV_INTERFACE_H */