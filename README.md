# Інструкція запуску лабораторної роботи №3 у Visual Studio

## Тема

**Навчання нейронної мережі засобами C++ з використанням бібліотеки mlpack**

Проєкт використовує:

- **C++**
- **Visual Studio 2026 Insiders**
- **vcpkg**
- **mlpack**
- **MNIST CSV dataset**
- **Armadillo / ensmallen** як залежності mlpack

---

# 1. Що потрібно встановити перед запуском

Перед відкриттям лабораторної роботи потрібно мати:

1. **Visual Studio 2026 Insiders**
2. Компонент Visual Studio:
   - `Desktop development with C++`
   - `MSVC C++ build tools`
   - `Windows SDK`
   - `C++ CMake tools for Windows`
3. **Git**
4. **PowerShell**
5. Інтернет для завантаження `vcpkg` і бібліотек

---

# 2. Де краще зберігати проєкт

Щоб уникнути проблем із C++ бібліотеками, краще не відкривати проєкт із папки, де є кирилиця або дуже довгий шлях.

Рекомендовано розпакувати лабораторну сюди:

```text
C:\Projects\Lab3_AIS
```

Наприклад:

```text
C:\Projects\Lab3_AIS\Lab3_AIS.sln
C:\Projects\Lab3_AIS\src
C:\Projects\Lab3_AIS\include
C:\Projects\Lab3_AIS\data
```

Небажано:

```text
C:\Users\Sevicss\Desktop\Лабораторки\СШІ\Лаб_3\...
```

Такий шлях може створювати проблеми для `vcpkg`, `CMake`, `OpenBLAS`, `LAPACK`.

---

# 3. Повне очищення старого vcpkg

Якщо раніше вже були невдалі спроби встановлення `vcpkg`, краще очистити все і поставити заново.

Відкрити **PowerShell від імені адміністратора**.

Виконати:

```powershell
if (Test-Path "C:\vcpkg\vcpkg.exe") {
    C:\vcpkg\vcpkg.exe integrate remove
}

Remove-Item -Recurse -Force "C:\vcpkg" -ErrorAction SilentlyContinue
Remove-Item -Recurse -Force "$env:LOCALAPPDATA\vcpkg\archives" -ErrorAction SilentlyContinue

reg delete HKCU\Environment /v VCPKG_ROOT /f
reg delete HKCU\Environment /v VCPKG_VISUAL_STUDIO_PATH /f
```

Якщо PowerShell напише, що змінної або папки не існує, це нормально.

---

# 4. Встановлення vcpkg з нуля

У PowerShell виконати:

```powershell
cd C:\

git clone https://github.com/microsoft/vcpkg.git C:\vcpkg

cd C:\vcpkg

.\bootstrap-vcpkg.bat
```

Після цього у папці `C:\vcpkg` має з’явитися файл:

```text
vcpkg.exe
```

---

# 5. Прив’язка vcpkg до Visual Studio 2026 Insiders

Для Visual Studio 2026 Insiders шлях зазвичай такий:

```text
C:\Program Files\Microsoft Visual Studio\18\Insiders
```

Виконати:

```powershell
$Env:VCPKG_ROOT = "C:\vcpkg"
$Env:VCPKG_VISUAL_STUDIO_PATH = "C:\Program Files\Microsoft Visual Studio\18\Insiders"

setx VCPKG_ROOT "C:\vcpkg"
setx VCPKG_VISUAL_STUDIO_PATH "C:\Program Files\Microsoft Visual Studio\18\Insiders"
```

Потім інтегрувати `vcpkg` у Visual Studio:

```powershell
cd C:\vcpkg

.\vcpkg.exe integrate install
```

Після цієї команди Visual Studio автоматично бачить бібліотеки, встановлені через `vcpkg`.

---

# 6. Встановлення mlpack

У PowerShell:

```powershell
cd C:\vcpkg

.\vcpkg.exe install mlpack:x64-windows
```

Ця команда встановить:

- `mlpack`
- `armadillo`
- `ensmallen`
- `cereal`
- `stb`
- `blas/lapack` залежності

Процес може тривати довго.

---

# 7. Якщо mlpack не встановлюється через OpenBLAS

Якщо установка падає на `openblas`, `lapack-reference`, `getarch_2nd`, `SGEMM_DEFAULT_UNROLL_M` або схожі помилки, це не проблема коду лабораторної.

Причина зазвичай у зв’язці:

```text
Visual Studio 2026 Insiders / Preview MSVC / vcpkg / OpenBLAS
```

У такому випадку найстабільніший варіант:

1. Встановити **Visual Studio 2022 Community** або **Build Tools 2022**.
2. У Visual Studio Installer вибрати:
   - `Desktop development with C++`
   - `MSVC v143`
   - `Windows SDK`
   - `C++ CMake tools for Windows`
3. Залишити VS 2026 як редактор, але для збірки використати стабільний toolset v143.

Після встановлення VS 2022 виконати:

```powershell
cd C:\vcpkg

$Env:VCPKG_VISUAL_STUDIO_PATH = "C:\Program Files\Microsoft Visual Studio\2022\Community"
setx VCPKG_VISUAL_STUDIO_PATH "C:\Program Files\Microsoft Visual Studio\2022\Community"

.\bootstrap-vcpkg.bat
.\vcpkg.exe integrate install
.\vcpkg.exe install mlpack:x64-windows
```

Потім у Visual Studio 2026 у властивостях проєкту можна поставити:

```text
Project → Properties → General → Platform Toolset → Visual Studio 2022 (v143)
```

---

# 8. Як відкрити лабораторну у Visual Studio
1. Розархівувати: Lab3_AIS/mnist_train.7z.
2. Відкрити **Visual Studio 2026 Insiders**.
3. Натиснути:

```text
File → Open → Project/Solution
```

4. Вибрати файл:

```text
Lab3_AIS.sln
```

або файл проєкту:

```text
Lab3_AIS.vcxproj
```

5. У верхній панелі Visual Studio вибрати:

```text
Release | x64
```

або:

```text
Debug | x64
```

Головне: має бути **x64**, не Win32.

---

# 9. Налаштування проєкту у Visual Studio

Відкрити:

```text
Project → Properties
```

Зверху поставити:

```text
Configuration: All Configurations
Platform: All Platforms
```

---

## 9.1. Стандарт C++

Перейти:

```text
C/C++ → Language → C++ Language Standard
```

Поставити:

```text
ISO C++17 Standard (/std:c++17)
```

або:

```text
ISO C++20 Standard (/std:c++20)
```

---

## 9.2. Вимкнення помилок C4996

Перейти:

```text
C/C++ → Preprocessor → Preprocessor Definitions
```

Додати:

```text
_CRT_SECURE_NO_WARNINGS;NOMINMAX;%(PreprocessorDefinitions)
```

Потім:

```text
C/C++ → Advanced → Disable Specific Warnings
```

Додати:

```text
4996
```

Потім:

```text
C/C++ → General → Treat Warnings As Errors
```

Поставити:

```text
No (/WX-)
```

Це потрібно, щоб Visual Studio не зупиняла збірку через попередження типу:

```text
'sprintf': This function or variable may be unsafe
'arma::Mat<double>::min': use .index_min() instead
```

---

## 9.3. Перевірка vcpkg

Якщо є вкладка:

```text
Project → Properties → vcpkg
```

перевірити:

```text
Use vcpkg: Yes
Triplet: x64-windows
```

Якщо вкладки немає, але виконано:

```powershell
.\vcpkg.exe integrate install
```

то MSBuild-проєкти Visual Studio все одно мають автоматично підхоплювати бібліотеки.

---

# 10. Важливо: не підключати mlpack вручну

Не потрібно:

- копіювати папку `mlpack` у проєкт;
- додавати `mlpack` як source-файли;
- додавати `add_subdirectory(mlpack)`;
- збирати тести mlpack;
- вручну додавати папки `librarys/mlpack`, `librarys/armadillo`, `librarys/ensmallen`.

Правильний варіант:

```cpp
#include <mlpack.hpp>
#include <mlpack/methods/ann/ffn.hpp>
```

А сама бібліотека підключається через `vcpkg`.

---

# 11. Запуск лабораторної

У Visual Studio:

```text
Build → Clean Solution
Build → Rebuild Solution
```

Після успішної збірки:

```text
Debug → Start Without Debugging
```

або клавіші:

```text
Ctrl + F5
```

У консолі має з’явитися приблизно таке:

```text
============================================================
 Лабораторна робота: навчання нейронної мережі
 Бібліотека: mlpack | Мова: C++ | Набір даних: MNIST
============================================================

[Етап] Завантаження навчальної вибірки
[Етап] Завантаження тестової вибірки
[Етап] Побудова нейронної мережі
[Етап] Навчання нейронної мережі
[Етап] Оцінювання на тестових даних

Правильних прогнозів: ...
Точність: ...%
```

# 14. Типові помилки

## Помилка: `Cannot open include file: mlpack.hpp`

Причина: `mlpack` не встановлено або Visual Studio не бачить `vcpkg`.

Рішення:

```powershell
cd C:\vcpkg
.\vcpkg.exe integrate install
.\vcpkg.exe install mlpack:x64-windows
```

Після цього перезапустити Visual Studio.

---

## Помилка: `Debug x86`, `Win32`

Потрібно вибрати:

```text
x64
```

а не:

```text
Win32
```

---

## Помилка: `arma::Mat<double>::min`

Це warning `4996`, який Visual Studio може сприймати як error.

Рішення:

```text
Disable Specific Warnings: 4996
Treat Warnings As Errors: No
```

---

## Помилка: `sprintf unsafe`

Рішення:

```text
Preprocessor Definitions:
_CRT_SECURE_NO_WARNINGS;NOMINMAX;%(PreprocessorDefinitions)
```

---

## Помилка: OpenBLAS не збирається

Якщо помилка виникає під час:

```powershell
vcpkg install mlpack:x64-windows
```

і в логах є:

```text
openblas
getarch_2nd
SGEMM_DEFAULT_UNROLL_M
-march=native
```

то це проблема збірки OpenBLAS з поточним MSVC Preview/Insiders.

Найстабільніше рішення:

- встановити Visual Studio 2022 Build Tools або Community;
- встановити `MSVC v143`;
- задати:

```powershell
setx VCPKG_VISUAL_STUDIO_PATH "C:\Program Files\Microsoft Visual Studio\2022\Community"
```

- повторити:

```powershell
cd C:\vcpkg
.\vcpkg.exe install mlpack:x64-windows
```

---

# 15. Коротка послідовність команд

```powershell
# 1. Встановлення vcpkg
cd C:\
git clone https://github.com/microsoft/vcpkg.git C:\vcpkg
cd C:\vcpkg
.\bootstrap-vcpkg.bat

# 2. Прив’язка до Visual Studio 2026 Insiders
setx VCPKG_ROOT "C:\vcpkg"
setx VCPKG_VISUAL_STUDIO_PATH "C:\Program Files\Microsoft Visual Studio\18\Insiders"

# 3. Інтеграція з Visual Studio
.\vcpkg.exe integrate install

# 4. Встановлення mlpack
.\vcpkg.exe install mlpack:x64-windows
```

---

# 16. Корисні джерела

- mlpack installation documentation
- vcpkg MSBuild integration documentation
- vcpkg environment variables documentation
- Visual Studio C++ project properties documentation
