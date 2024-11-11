double anneal() {
  mt19937 rnd_engine(time(0));
  uniform_real_distribution<double> rng(0, 1);
  const double dT = 0.001;
  // Argument p
  double S_cur = calc(p), S_best = S_cur;
  for (double T = 2000; T > eps; T -= dT) {
    // Modify p to p_prime
    const double S_prime = calc(p_prime);
    const double delta_c = S_prime - S_cur;
    double prob = min((double)1, exp(-delta_c / T));
    if (rng(rnd_engine) <= prob)
      S_cur = S_prime, p = p_prime;
    if (S_prime < S_best) // find min
      S_best = S_prime, p_best = p_prime;
  }
  return S_best;
}