% graficar_complejidad.m
% Script de MATLAB para graficar la complejidad de algoritmos

% Leer los datos de complejidad generados por el programa C++
try
    datos = readtable('datos_complejidad.csv');
catch
    error('No se encontró el archivo datos_complejidad.csv. Ejecute primero el programa C++.');
end

% Obtener valores de n y tiempos
n_valores = datos.n;

% Funciones para modelar diferentes complejidades
modelo_constante = @(a, n) a * ones(size(n));
modelo_logaritmico = @(a, b, n) a * log(n) + b;
modelo_lineal = @(a, b, n) a * n + b;
modelo_nlogn = @(a, b, n) a * n .* log(n) + b;
modelo_cuadratico = @(a, b, n) a * n.^2 + b;

% Función para analizar complejidad
function [mejor_nombre, prediccion] = analizar_complejidad(n_valores, tiempos)
    % Modelos para probar
    modelos = {
        @(x, n) x(1) * ones(size(n)), 'O(1)';
        @(x, n) x(1) * log(n) + x(2), 'O(log n)';
        @(x, n) x(1) * n + x(2), 'O(n)';
        @(x, n) x(1) * n .* log(n) + x(2), 'O(n log n)';
        @(x, n) x(1) * n.^2 + x(2), 'O(n^2)'
    };
    
    mejor_error = inf;
    mejor_nombre = '';
    prediccion = [];
    
    for i = 1:size(modelos, 1)
        modelo = modelos{i, 1};
        try
            % Ajustar modelo
            if strcmp(modelos{i, 2}, 'O(1)')
                x0 = [mean(tiempos)];
            else
                x0 = [1, 0]; % Parámetros iniciales
            end
            
            % Función para optimizar
            f = @(x) sum((modelo(x, n_valores) - tiempos).^2);
            
            % Optimizar
            options = optimset('Display', 'off');
            if length(x0) == 1
                [x_opt, error] = fminsearch(@(x) f(x), x0, options);
            else
                [x_opt, error] = fminsearch(@(x) f([x(1), x(2)]), x0, options);
            end
            
            % Calcular predicción
            pred = modelo(x_opt, n_valores);
            
            % Calcular error
            error_modelo = mean((pred - tiempos).^2);
            
            if error_modelo < mejor_error
                mejor_error = error_modelo;
                mejor_nombre = modelos{i, 2};
                prediccion = pred;
            end
        catch
            % Ignorar si el ajuste falla
            continue;
        end
    end
end

% Crear figura
figure('Position', [100, 100, 1200, 900]);

% Operaciones y colores
operaciones = {
    'suma_tiempo', 'Suma', 'blue';
    'resta_tiempo', 'Resta', 'green';
    'multiplicacion_tiempo', 'Multiplicación', 'red';
    'division_tiempo', 'División', 'magenta'
};

% Graficar cada operación
for i = 1:size(operaciones, 1)
    columna = operaciones{i, 1};
    nombre = operaciones{i, 2};
    color = operaciones{i, 3};
    
    tiempos = datos.(columna);
    
    % Analizar complejidad
    [complejidad, prediccion] = analizar_complejidad(n_valores, tiempos);
    
    % Crear subplot
    subplot(2, 2, i);
    
    % Graficar datos originales
    scatter(n_valores, tiempos, 50, color, 'filled', 'DisplayName', 'Datos');
    hold on;
    
    % Graficar curva de ajuste
    n_fit = linspace(min(n_valores), max(n_valores), 100);
    [complejidad_ajuste, ~] = analizar_complejidad(n_valores, tiempos);
    
    % Mostrar línea de tendencia
    if ~isempty(prediccion)
        plot(n_valores, prediccion, 'k--', 'LineWidth', 2, 'DisplayName', ['Ajuste: ', complejidad]);
    end
    
    title([nombre, ' - Complejidad: ', complejidad], 'FontSize', 12);
    xlabel('Tamaño (n)', 'FontSize', 10);
    ylabel('Tiempo (ms)', 'FontSize', 10);
    grid on;
    legend('Location', 'northwest');
    
    hold off;
end

% Ajustar diseño
sgtitle('Análisis de Complejidad Computacional', 'FontSize', 16);
set(gcf, 'Color', 'w');
saveas(gcf, 'complejidad_matlab.png');
disp('Gráfica guardada como "complejidad_matlab.png"');