int get_root(int n, int P) { // ensure 0 <= n < p
  if (P == 2 or n == 0) return n;
  auto check = [&](ll x) {
    return fpow(ll(x), (P - 1) / 2, P); };
  if (check(n) != 1) return -1;
  mt19937 rnd(7122); ll z = 1, w;
  while (check(w = (z * z - n + P) % P) != P - 1)
    z = rnd() % P;
  const auto M = [&](auto &u, auto &v) {
    auto [a, b] = u; auto [c, d] = v;
    return make_pair((a * c + b * d % P * w) % P,
        (a * d + b * c) % P);
  };
  pll r(1, 0), e(z, 1);
  for (int q = (P + 1) / 2; q; q >>= 1, e = M(e, e))
    if (q & 1) r = M(r, e);
  return ll(r.first); // sqrt(n) mod P where P is prime
}
