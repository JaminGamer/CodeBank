#ifndef __ImGUIStyles_h_
#define __ImGUIStyles_h_

void SetImGUIStyle(ImVec4 a_Colors[], int a_Size, float a_Alpha, bool a_IsDark = true);
std::vector<ImVec4> GetStyleColorArray(int style);

#endif // __ImGUIStyles_h_