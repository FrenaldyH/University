import math

class Power4:
    def __init__(self):
        self.powers = [0] * 32
        self.powers[0] = 1 
        for i in range(1, 32):
            self.powers[i] = self.powers[i - 1] * 4
    
    def __call__(self, k):
        return self.powers[k]

class Trapezoid:
    def __init__(self, func, a, b):
        self.func = func
        self.a = float(a)
        self.b = float(b)

    def solve(self, pias):
        if pias == 0:
            return 0.0
        h = (self.b - self.a) / pias
        integralSum = self.func(self.a) + self.func(self.b)
        for i in range(1, pias):
            integralSum += 2 * self.func(self.a + i * h)
        result = (h / 2) * integralSum
        return result
    
class Romberg:
    def __init__(self, func, a, b):
        self.mat = []
        self.func = func
        self.a = float(a)
        self.b = float(b)
        self.max_iteration = 15
        self.tolerance = 1.0e-7
        self.power_of_4 = Power4() 
        self.trapezoid = Trapezoid(func, a, b)
        
    def solve(self):
        self.mat = []
        
        self.mat.append([self.trapezoid.solve(1)])

        pias = 1
        for i in range(1, self.max_iteration):
            pias *= 2
            newRow = [self.trapezoid.solve(pias)]

            for j in range(1, i + 1):
            
                t1 = self.power_of_4(j) * newRow[j - 1]
                t2 = self.mat[i - 1][j - 1]
                rombergVal = (t1 - t2) / (self.power_of_4(j) - 1)
                newRow.append(rombergVal)
            
            self.mat.append(newRow)
            if abs(self.mat[i][i] - self.mat[i - 1][i - 1]) < self.tolerance:
                return self.mat[i][i]
        
        print(f"Peringatan: Solusi tidak konvergen dalam {self.max_iteration} iterasi.")
        return self.mat[-1][-1]
            
def myFunc(x):
    return x**2 + 3 * x + 4

lower_bound = 0
upper_bound = 10

print(f"Menghitung integral dari f(x) = x^2 + 3x + 4 dari {lower_bound} sampai {upper_bound}")
print("-" * 50)

print("## Menggunakan Metode Trapesium ##")
trapezoidTemp = Trapezoid(myFunc, lower_bound, upper_bound)
    
hasilPias10 = trapezoidTemp.solve(pias=10)
print(f"Hasil Trapesium dengan n=10   : {hasilPias10:.10f}")
    
hasilPias100 = trapezoidTemp.solve(pias=100)
print(f"Hasil Trapesium dengan n=100  : {hasilPias100:.10f}")
    
print("-" * 50)

print("## Menggunakan Metode Romberg ##")
rombergTemp = Romberg(myFunc, lower_bound, upper_bound)
hasilRomberg = rombergTemp.solve()
print(f"Hasil Romberg (akurat)      : {hasilRomberg:.10f}")

hasilEksak = (10**3 / 3) + (3 * 10**2 / 2) + (4 * 10)
print(f"Hasil Eksak (Analitik)    : {hasilEksak:.10f}")
print("-" * 50)
