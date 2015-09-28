function C = buildC( A )
    n = length(A);
    I = eye(n);
    C = kron(A,I) + kron(I,A);
end

