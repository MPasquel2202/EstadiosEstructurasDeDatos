% Datos de medición
n = [100 300 500 700 900 1100 1300 1500 1700 1900 ];
t = [7.575e-06 2.2702e-05 3.8312e-05 8.7604e-05 8.1212e-05 0.000103293 0.000121047 0.000137067 0.000173756 0.000176561 ];

% Modelos de complejidad
models = {
  'n', n;
  'n^2', n.^2;
  'n^3', n.^3;
  'log n', log(n);
  'n log n', n.*log(n);
  '2^n', 2.^n;
  'n!', arrayfun(@(x) factorial(min(x,10)), n)
};

% Ajuste y error
errors = zeros(size(models,1),1);
scales = zeros(size(models,1),1);

for i = 1:size(models,1)
  f = models{i,2};
  a = (f * t') / (f * f');
  scales(i) = a;
  errors(i) = norm(a*f - t);
end

figure; hold on; grid on;
plot(n, t, 'ko', 'DisplayName', 'Datos reales');
for i = 1:size(models,1)
  plot(n, scales(i)*models{i,2}, 'DisplayName', models{i,1});
end
xlabel('Tamaño de entrada n');
ylabel('Tiempo (s)');
title('Análisis de Complejidad Big-O');
legend('show');

[bestError, idx] = min(errors);
fprintf('Mejor ajuste Big-O: %s\n', models{idx,1});
