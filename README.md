<div align="center">

# 📅 `clsDate` — Modern C++ Date & Calendar Engine

**A lightweight, self-contained C++ date manipulation and calendar toolkit providing robust date arithmetic, business-day tracking, and calendar rendering.**

[![Language](https://img.shields.io/badge/Language-C%2B%2B11%20%7C%20C%2B%2B14%20%7C%20C%2B%2B17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B)
[![Compiler](https://img.shields.io/badge/Compiler-MSVC%20%2F%20Visual%20Studio-0078d7.svg)](https://visualstudio.microsoft.com/)
[![License](https://img.shields.io/badge/License-MIT%20%2F%20Educational-green.svg)](#-license)
[![Maintenance](https://img.shields.io/badge/Maintained-Yes-success.svg)](#)

[Key Features](#-key-features) • [Quick Start](#-quick-start) • [API Reference](#-api-reference) • [Business Logic](#-business--workday-rules) • [Author](#-author)

</div>

---

## 🌟 Key Features

- **Dual-Interface Paradigm:** Every operation is exposed as both an **OOP Instance Method** (operating on the current object) and an efficient **Static Utility Function**.
- **Versatile Instantiation:** Construct dates from system time, explicit `(D, M, Y)` integers, ordinal day-of-year values, or string representations (`DD/MM/YYYY`).
- **Full Date Arithmetic:** Step forward or backward across units of time: days, weeks, months, years, decades, centuries, and millennia.
- **Accurate Calendar Algorithms:** Implements Gregorian leap-year validation and Sakamoto’s algorithm for constant-time $O(1)$ day-of-week calculation.
- **Workday & Leave Management:** Built-in business day identification, vacation length calculators, and expected return-date computation.
- **Terminal Calendar Views:** Render formatted monthly and full-year calendars directly to the standard console.

---

## 🏗️ Architecture & Storage

The class internally models a date in the Gregorian calendar:

```cpp
class clsDate
{
private:
    short _Day;
    short _Month;
    short _Year;
public:
    // MSVC Property syntax allows field-like assignments:
    __declspec(property(get = GetDay, put = SetDay)) int Day;
    __declspec(property(get = GetMonth, put = SetMonth)) int Month;
    __declspec(property(get = GetYear, put = SetYear)) int Year;
};

```

---

## 🚀 Quick Start

### Prerequisites

* A modern C++ compiler targeting **C++11** or later.
* Microsoft Visual C++ (MSVC) is required for `__declspec(property)` syntax support.
* Auxiliary dependency: `clsString.h` (for tokenizing date strings via `clsString::SplitString`).

### Basic Example

```cpp
#include <iostream>
#include "clsDate.h"

int main()
{
    // 1. Initialize from system clock
    clsDate today;
    std::cout << "Today: ";
    today.Print();

    // 2. Parse string date & advance by 1 week
    clsDate projectDeadline("25/09/2026");
    projectDeadline.IncreaseDateByOneWeek();
    
    std::cout << "Extended Deadline: " << projectDeadline.DateToString() << std::endl;

    // 3. Compute business days
    clsDate leaveStart(1, 10, 2026);
    clsDate leaveEnd(15, 10, 2026);
    short workingDays = clsDate::CalculateVactionDays(leaveStart, leaveEnd);
    
    std::cout << "Actual working days off: " << workingDays << std::endl;

    return 0;
}

```

---

## 🔧 Constructors

| Constructor Signature | Description | Example |
| --- | --- | --- |
| `clsDate()` | Initializes with the current local machine date. | `clsDate now;` |
| `clsDate(std::string Date)` | Parses a formatted string (`DD/MM/YYYY`). | `clsDate d("25/09/2026");` |
| `clsDate(short Day, short Month, short Year)` | Explicit component-wise assignment. | `clsDate d(25, 9, 2026);` |
| `clsDate(short DayOrderInYear, short Year)` | Resolves day ordinal ($1 \dots 366$) to calendar date. | `clsDate d(268, 2026);` |

---

## 📖 API Reference

### 1. Date Information & Temporal Metrics

All methods below are available both as static (`clsDate::Method(Year, Month)`) and member (`dateInstance.Method()`) functions.

| Method | Return Type | Description |
| --- | --- | --- |
| `IsLeapYear(Year)` | `bool` | Validates whether a year is leap using standard Gregorian rules. |
| `NumberOfDaysInYear(Year)` | `int` | Returns `366` for leap years, `365` otherwise. |
| `NumberOfHoursInYear(Year)` | `int` | Computes total hours in the specified year. |
| `NumberOfMinutsInYear(Year)` | `int` | Computes total minutes in the specified year. |
| `NumberOfSecendsInYear(Year)` | `int` | Computes total seconds in the specified year. |
| `NumberOfDaysInMonth(Year, Month)` | `short` | Returns total days in the month (adjusts Feb for leap years). |
| `DayOfWeekOrder(Year, Month, Day)` | `short` | Computes weekday index (`0 = Sun`, `1 = Mon`, $\dots$, `6 = Sat`). |
| `DayShortName(DayIndex)` | `std::string` | Returns abbreviation (`"Sun"`, `"Mon"`, etc.). |
| `MonthShortName(Month)` | `std::string` | Returns month abbreviation (`"Jan"`, `"Feb"`, etc.). |

---

### 2. Date Arithmetic & Step Functions

Mutators that adjust date states forward or backward.

```
       Increase / Advance                       Decrease / Rollback
┌──────────────────────────────┐        ┌──────────────────────────────┐
│ AddDaysToDate(...)           │        │ DecreaseDateByOneDay()       │
│ IncreaseDateByXDays(...)     │        │ DecreaseDateByXDay(...)      │
│ IncreaseDateByOneWeek()      │  <──>  │ DecreaseDateByOneWeek()      │
│ IncreaseDateByXMonths(...)   │        │ DecreaseDateByXMonth(...)    │
│ IncreaseDateByXYears(...)    │        │ DecreaseDateByXYear(...)     │
│ IncreaseDateByOneDecade()    │        │ DecreaseDateByOneDecade()    │
│ IncreaseDateByOneCentury()   │        │ DecreaseDateByOneCentury()   │
│ IncreaseDateByOneMillennium()│        │ DecreaseDateByOneMillennium()│
└──────────────────────────────┘        └──────────────────────────────┘

```

---

### 3. Comparison & Interval Measurement

The class exposes clear comparison utilities and safe signed interval counters:

```cpp
enum enDateCompare { Befor = -1, Equal = 0, After = 1 };

```

* `IsDate1BeforeDate2(d1, d2)`: Evaluates if `d1 < d2`.
* `IsDate1EqualDate2(d1, d2)`: Evaluates if `d1 == d2`.
* `IsDate1AfterDate2(d1, d2)`: Evaluates if `d1 > d2`.
* `CompareDate(d1, d2)`: Returns an `enDateCompare` relative state.
* `GetDifferenceInDays(d1, d2, IncludeEndDay)`: Calculates absolute/signed day difference.
* `CalculateYourAgeInDays(DateOfBirth)`: Measures lifespan elapsed from birth to today.

---

## 💼 Business & Workday Rules

The library embeds business calendar assumptions tailored for regions observing a **Friday/Saturday** weekend:

| Day Type | Days Included | `IsBusinessDay()` | `IsWeekEnd()` |
| --- | --- | --- | --- |
| **Business Days** | Sunday, Monday, Tuesday, Wednesday, Thursday | ✅ `true` | ❌ `false` |
| **Weekend** | Friday, Saturday | ❌ `false` | ✅ `true` |

### Vacation Workflows

* **`CalculateVactionDays(DateFrom, DateTo)`:** Loops through the interval, skipping weekends, and returns the net working days consumed.
* **`CalculateVactionDaysReturnDate(DateFrom, VactionDays)`:** Computes the calendar return date by taking an approved duration of business days and jumping over weekend interruptions.

---

## 🖥️ Terminal Calendar Output

Render clean, aligned ASCII calendars directly inside console terminals:

```cpp
clsDate::PrintMonthCalendar(2026, 9);

```

```text
---------------------------Sep---------------------------

   Sun   Mon   Tue   Wed   Thu   Fri   Sat
                 1     2     3     4     5
     6     7     8     9    10    11    12
    13    14    15    16    17    18    19
    20    21    22    23    24    25    26
    27    28    29    30
---------------------------------------------------------

```

---

## 📁 Repository Layout

```text
clsDate/
├── clsDate.h          # Core implementation and class definitions
├── clsString.h        # String tokenizer helper dependency
├── main.cpp           # Demo driver and unit tests
└── README.md          # Project documentation

```

---

## ⚙️ Technical Considerations & Errata

> **Note for production consumers:**
> 1. **MSVC Properties:** The property extension `__declspec(property)` is proprietary to Microsoft Visual Studio. For pure cross-platform builds (`g++`, `clang++`), prefer standard getters/setters: `GetDay()` and `SetDay()`.
> 2. **Legacy Naming:** Several identifiers maintain historical naming conventions to preserve legacy ABI compatibility (e.g., `NumberOfMinutsInYear`, `Secends`, `Vaction`, `Befor`).
> 
> 

---

## 👨‍💻 Author

**Yousif Aljaberi**

Software Engineer 

---

