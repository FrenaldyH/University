import math
import matplotlib.pyplot as plt
import numpy as np

def regula_falsi(fungsi, a, b, iterasi, grafik):

    def log(x):
        if x <= 0:
            raise ValueError(f"log() domain error: x = {x} (harus x > 0)")
        return math.log10(x)
    
    def ln(x):
        if x <= 0:
            raise ValueError(f"log() domain error: x = {x} (harus x > 0)")
        return math.log(x)
    
    def sin(x):
        return math.sin(x)
    
    def cos(x):
        return math.cos(x)
    
    def tan(x):
        return math.tan(x)
    
    def sqrt(x):
        if x < 0:
            raise ValueError(f"sqrt() domain error: x = {x} (harus x >= 0)")
        return math.sqrt(x)
    
    def exp(x):
        return math.exp(x)
    
    safe_dict = {
        'x': 0, 
        'log': log,
        'ln': ln,
        'sin': sin,
        'cos': cos,
        'tan': tan,
        'sqrt': sqrt,
        'exp': exp,
        'pi': math.pi,
        'e': math.e,
        '__builtins__': {}
    }
    
    def f(x_val):
        safe_dict['x'] = x_val
        return eval(fungsi, safe_dict)

    iterations_data = []
    a_vals = [a]
    b_vals = [b]
    c_vals = []

    if f(a) * f(b) >= 0:
        print("Tidak ada atau terdapat banyak akar penyelesaian, " \
            "metode regula falsi tidak valid untuk rentang ini.")
        quit()

    print("\n" + "=" * 55)
    print(f"{'Iter':<4} {'a':<12} {'b':<12} {'c':<12} {'f(c)':<12}")
    print("-" * 55)

    i = 0;
    while i < iterasi:

        c = (a * f(b) - b * f(a)) / (f(b) - f(a))

        iterations_data.append({
            'iter': i + 1,
            'a': a,
            'b': b,
            'c': c,
            'fc': f(c)
        })

        c_vals.append(c)

        print(f"{i+1:<4} {a:<12.6f} {b:<12.6f} {c:<12.6f} {f(c):<12.6f}")

        if f(c) * f(a) < 0:
            b = c
            b_vals.append(b)
            i = i + 1

        elif f(c) * f(b) < 0:
            a = c
            a_vals.append(a)
            i = i + 1

        elif abs(f(c)) < 1e-10:
            break

        else:
            print("Terdapat aksi yang invalid.")
            quit()

    print()
    if i < iterasi:
        print("Selesai lebih awal dengan jumlah iterasi lebih sedikit")
    print(f"Sejumlah {i} iterasi telah dilakukan")

    print()
    print("Hasil:")
    print(f"akar x = {c}")
    print(f"batas bawah b = {b}")
    print(f"batas atas  a = {a}")

    if grafik:
        fig, (ax1) = plt.subplots(1, 1, figsize=(10, 5))
        fig.suptitle(f'Visualisasi Metode Regula Falsi untuk f(x) = {fungsi}', fontsize=14, fontweight='bold')

        x_range = abs(b_vals[0] - a_vals[0])
        x_min = min(a_vals[0], b_vals[0]) - 0.2 * x_range
        x_max = max(a_vals[0], b_vals[0]) + 0.2 * x_range
        
        x = np.linspace(x_min, x_max, 1000)
        y = []
    
        for xi in x:
            try:
                yi = f(xi)
                if math.isnan(yi) or math.isinf(yi):
                    yi = None
            except:
                yi = None
            y.append(yi)
    
        ax1.plot(x, y, 'b-', linewidth=2, label=f'f(x) = {fungsi}')
        ax1.axhline(y=0, color='k', linestyle='--', alpha=0.3, label='y = 0')
        ax1.grid(True, alpha=0.3)
        
        for i, data in enumerate(iterations_data):
            a_i, b_i, c_i = data['a'], data['b'], data['c']
            fa_i, fb_i, fc_i = f(a_i), f(b_i), data['fc']
            
            ax1.plot([a_i, b_i], [fa_i, fb_i], 'r-', alpha=0.7, linewidth=1)
            ax1.plot([a_i, c_i], [fa_i, 0], 'r--', alpha=0.5)
            ax1.plot([b_i, c_i], [fb_i, 0], 'r--', alpha=0.5)
            
            ax1.plot(a_i, fa_i, 'ro', markersize=6, alpha=0.8)
            ax1.plot(b_i, fb_i, 'ro', markersize=6, alpha=0.8)
            ax1.plot(c_i, fc_i, 'go', markersize=8, alpha=0.8)
            
            if i < 5:  # Hanya 5 iterasi pertama, agar grafik tidak terlalu penuh
                ax1.annotate(f'c{i+1}', (c_i, fc_i), xytext=(5, 5), 
                            textcoords='offset points', fontsize=8)
        
        ax1.plot(c, f(c), 'r*', markersize=15, label=f'Akar ≈ {c:.6f}')
        
        ax1.set_xlabel('x')
        ax1.set_ylabel('f(x)')
        ax1.legend()
        ax1.grid(True, alpha=0.3)

        plt.tight_layout()
        plt.show()

print("------------------")
print("|  REGULA FALSI  |")
print("------------------")

print("Operasi yang didukung: +, -, *, /, **")
print("Fungsi tambahan yang didukung:")
print("> Trigonometri: sin(x), cos(x), tan(x)")
print("> Eksponen: ln(x), log(x), exp(x), sqrt(x)")
print("Konstanta yang didukung: e, pi")

print("--------------------")

fungsi = input("Input fungsi: ")
b = float(input("Input batas bawah: "))
a = float(input("Input batas  atas: "))
iterasi = int(input("Input jumlah iterasi: "))
grafik = input("Tampilkan grafik? (y/n): ").lower().startswith('y')

regula_falsi(fungsi, a, b, iterasi, grafik)
input("Enter to continue..")
