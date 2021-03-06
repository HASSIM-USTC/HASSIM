/**
 * git clone https://github.com/hou-dao/deom.git
 * ---
 * Written by Houdao Zhang 
 * mailto: houdao@connect.ust.hk
 */
#include "deom2.hpp"
#include <cmath>


void deom2::remSch(cx_cube &dtotal, const cx_cube &total, const double t) {
  printf("s\n");
  const int nsav = nddo;
  dtotal.slices(0, nddo - 1).zeros();

  cx_cube qddo1(size(qmd1));
  cx_cube ddoq1(size(qmd1));
  cx_cube qddo2(size(qmd2));
  cx_cube ddoq2(size(qmd2));

  for (int iado = 0; iado < nsav; ++iado) {
    const cx_mat &ado = total.slice(iado);
    if (iado == 0 || is_valid(ado)) {
      const hnod &nod = keys(iado);
      ivec key0(nod.key);
      int tier = tree.find(key0)->tier;

      dtotal.slice(iado) += -deom_ci * (ham1 * ado - ado * ham1) - nod.gams * ado;
      for (int m = 0; m < nmod; ++m) {
        qddo1.slice(m) = qmd1.slice(m) * ado;
        ddoq1.slice(m) = ado * qmd1.slice(m);
        qddo2.slice(m) = qmd2.slice(m) * ado;
        ddoq2.slice(m) = ado * qmd2.slice(m);
      }

      for (int mp = 0; mp < nind; ++mp) { // contribute to same tier
        for (int nq = 0; nq < nind; ++nq) {
          const int m = modLabel(mp);
          const int n = modLabel(nq);
          if (m == n && abs(alpha2(m)) > 1.0e-15) {
            ivec key1 = gen_key(gen_key(key0, mp, 1), nq, -1);
            if (!key1.is_empty()) {
              const int k = (key1.n_rows < (unsigned int)(mp + 1)) ? 0 : (key1(mp));
              const int l = ((key1.n_rows < (unsigned int)(nq + 1)) ? 1 : (key1(nq) + 1)) - ((mp == nq) ? 1 : 0);
              const cx_double sn = -deom_ci * 2.0 * alpha2(m) * sqrt(k * l * coef_abs(nq) / coef_abs(mp));
              const cx_double cl = sn * coef_lft(mp);
              const cx_double cr = sn * coef_rht(mp);
              if (!tree.try_insert(key1, nddo)) {
                int loc = tree.find(key1)->rank;
                dtotal.slice(loc) += cl * qddo2.slice(m) - cr * ddoq2.slice(m);
              } else {
                keys(nddo) = hnod(nod.gams + expn(mp) - expn(nq), key1);
                dtotal.slice(nddo) = cl * qddo2.slice(m) - cr * ddoq2.slice(m);
                nddo += 1;
              }
            }
          }
        }
      }

      if (tier < lmax - 1) { // contribute to tier+2
        for (int mp = 0; mp < nind; ++mp) {
          for (int nq = 0; nq < nind; ++nq) {
            const int m = modLabel(mp);
            const int n = modLabel(nq);
            if (m == n && abs(alpha2(m)) > 1.0e-15) {
              ivec key1 = gen_key(gen_key(key0, mp, 1), nq, 1);
              int k = key1(mp);
              int l = key1(nq) - ((mp == nq) ? 1 : 0);
              const cx_double sn = -deom_ci * alpha2(m) * sqrt(k * l / (coef_abs(nq) * coef_abs(mp)));
              const cx_double cl = sn * coef_lft(mp) * coef_lft(nq);
              const cx_double cr = sn * coef_rht(mp) * coef_rht(nq);
              if (!tree.try_insert(key1, nddo)) {
                int loc = tree.find(key1)->rank;
                dtotal.slice(loc) += cl * qddo2.slice(m) - cr * ddoq2.slice(m);
              } else {
                keys(nddo) = hnod(nod.gams + expn(mp) + expn(nq), key1);
                dtotal.slice(nddo) = cl * qddo2.slice(m) - cr * ddoq2.slice(m);
                nddo += 1;
              }
            }
          }
        }
      }

      for (int mp = 0; mp < nind; ++mp) { // contribute to tier-2
        for (int nq = 0; nq < nind; ++nq) {
          const int m = modLabel(mp);
          const int n = modLabel(nq);
          if (m == n && abs(alpha2(m)) > 1.0e-15) {
            ivec key1 = gen_key(gen_key(key0, mp, -1), nq, -1);
            if (!key1.empty()) {
              int k = key0(mp);
              int l = key0(nq) - ((mp == nq) ? 1 : 0);
              const cx_double sn = -deom_ci * alpha2(m) * sqrt(k * l * coef_abs(mp) * coef_abs(nq));
              if (!tree.try_insert(key1, nddo)) {
                int loc = tree.find(key1)->rank;
                dtotal.slice(loc) += sn * (qddo2.slice(m) - ddoq2.slice(m));
              } else {
                keys(nddo) = hnod(nod.gams - expn(mp) - expn(nq), key1);
                dtotal.slice(nddo) = sn * (qddo2.slice(m) - ddoq2.slice(m));
                nddo += 1;
              }
            }
          }
        }
      }

      if (tier < lmax) { // to tier+1
        for (int mp = 0; mp < nind; ++mp) {
          ivec key1 = gen_key(key0, mp, 1);
          const int m = modLabel(mp);
          const int k = key1(mp);
          const cx_double sn = -deom_ci * alpha1(m) * sqrt(k / coef_abs(mp));
          const cx_double cl = sn * coef_lft(mp);
          const cx_double cr = sn * coef_rht(mp);
          if (!tree.try_insert(key1, nddo)) {
            int loc = tree.find(key1)->rank;
            dtotal.slice(loc) += cl * qddo1.slice(m) - cr * ddoq1.slice(m);
          } else {
            keys(nddo) = hnod(nod.gams + expn(mp), key1);
            dtotal.slice(nddo) = cl * qddo1.slice(m) - cr * ddoq1.slice(m);
            nddo += 1;
          }
        }
      }

      for (int mp = 0; mp < nind; ++mp) { // to tier-1
        ivec key1 = gen_key(key0, mp, -1);
        if (!key1.is_empty()) {
          const int m = modLabel(mp);
          const int k = (key1.n_rows < (unsigned int)(mp + 1)) ? 1 : (key1(mp) + 1);
          const cx_double sn = -deom_ci * alpha1(m) * sqrt(k * coef_abs(mp));
          if (!tree.try_insert(key1, nddo)) {
            int loc = tree.find(key1)->rank;
            dtotal.slice(loc) += sn * (qddo1.slice(m) - ddoq1.slice(m));
          } else {
            keys(nddo) = hnod(nod.gams - expn(mp), key1);
            dtotal.slice(nddo) = sn * (qddo1.slice(m) - ddoq1.slice(m));
            nddo += 1;
          }
        }
      }
    }
  }
}

void deom2::remHei(cx_cube &dtotal, const cx_cube &total, const double t) {
  printf("h\n");
  const int nsav = nddo;
  dtotal.slices(0, nddo - 1).zeros();

  cx_cube qddo1(size(qmd1));
  cx_cube ddoq1(size(qmd1));
  cx_cube qddo2(size(qmd2));
  cx_cube ddoq2(size(qmd2));

  for (int iado = 0; iado < nsav; ++iado) {
    const cx_mat &ado = total.slice(iado);
    if (iado == 0 || is_valid(ado)) {
      const hnod &nod = keys(iado);
      ivec key0(nod.key);
      int tier = tree.find(key0)->tier;

      dtotal.slice(iado) += -deom_ci * (ado * ham1 - ham1 * ado) - nod.gams * ado;
      for (int m = 0; m < nmod; ++m) {
        qddo1.slice(m) = qmd1.slice(m) * ado;
        ddoq1.slice(m) = ado * qmd1.slice(m);
        qddo2.slice(m) = qmd2.slice(m) * ado;
        ddoq2.slice(m) = ado * qmd2.slice(m);
      }

      for (int mp = 0; mp < nind; ++mp) { // contribute to same tier
        for (int nq = 0; nq < nind; ++nq) {
          const int m = modLabel(mp);
          const int n = modLabel(nq);
          if (m == n) {
            ivec key1 = gen_key(gen_key(key0, nq, 1), mp, -1);
            if (!key1.is_empty()) {
              const int k = ((key1.n_rows < (unsigned int)(mp + 1)) ? 1 : (key1(mp) + 1)) - ((mp == nq) ? 1 : 0);
              const int l = (key1.n_rows < (unsigned int)(nq + 1)) ? 0 : (key1(nq));
              const cx_double sn = -deom_ci * 2.0 * alpha2(m) * sqrt(k / coef_abs(mp) * l * coef_abs(nq));
              const cx_double cl = sn * coef_lft(mp);
              const cx_double cr = sn * coef_rht(mp);
              if (!tree.try_insert(key1, nddo)) {
                int loc = tree.find(key1)->rank;
                dtotal.slice(loc) += cl * ddoq2.slice(m) - cr * qddo2.slice(m);
              } else {
                keys(nddo) = hnod(nod.gams - expn(mp) + expn(nq), key1);
                dtotal.slice(nddo) = cl * ddoq2.slice(m) - cr * qddo2.slice(m);
                nddo += 1;
              }
            }
          }
        }
      }

      if (tier < lmax - 1) { // contribute to tier+2
        for (int mp = 0; mp < nind; ++mp) {
          for (int nq = 0; nq < nind; ++nq) {
            const int m = modLabel(mp);
            const int n = modLabel(nq);
            if (m == n) {
              ivec key1 = gen_key(gen_key(key0, mp, 1), nq, 1);
              int k = key1(mp);
              int l = key1(nq) - ((mp == nq) ? 1 : 0);
              const cx_double sn = -deom_ci * alpha2(m) * sqrt(k * coef_abs(mp) * l * coef_abs(nq));
              if (!tree.try_insert(key1, nddo)) {
                int loc = tree.find(key1)->rank;
                dtotal.slice(loc) += sn * (ddoq2.slice(m) - qddo2.slice(m));
              } else {
                keys(nddo) = hnod(nod.gams + expn(mp) + expn(nq), key1);
                dtotal.slice(nddo) = sn * (ddoq2.slice(m) - qddo2.slice(m));
                nddo += 1;
              }
            }
          }
        }
      }

      for (int mp = 0; mp < nind; ++mp) { // contribute to tier-2
        for (int nq = 0; nq < nind; ++nq) {
          const int m = modLabel(mp);
          const int n = modLabel(nq);
          if (m == n) {
            ivec key1 = gen_key(gen_key(key0, mp, -1), nq, -1);
            if (!key1.empty()) {
              int k = key0(mp);
              int l = key0(nq) - ((mp == nq) ? 1 : 0);
              const cx_double sn = -deom_ci * alpha2(m) * sqrt(k / coef_abs(mp) * l / coef_abs(nq));
              const cx_double cl = sn * coef_lft(mp) * coef_lft(nq);
              const cx_double cr = sn * coef_rht(mp) * coef_rht(nq);
              if (!tree.try_insert(key1, nddo)) {
                int loc = tree.find(key1)->rank;
                dtotal.slice(loc) += cl * ddoq2.slice(m) - cr * qddo2.slice(m);
              } else {
                keys(nddo) = hnod(nod.gams - expn(mp) - expn(nq), key1);
                dtotal.slice(nddo) = cl * ddoq2.slice(m) - cr * qddo2.slice(m);
                nddo += 1;
              }
            }
          }
        }
      }

      if (tier < lmax) { // to tier+1
        for (int mp = 0; mp < nind; ++mp) {
          ivec key1 = gen_key(key0, mp, 1);
          const int m = modLabel(mp);
          const int k = key1(mp);
          const cx_double sn = -deom_ci * alpha1(m) * sqrt(k * coef_abs(mp));
          if (!tree.try_insert(key1, nddo)) {
            int loc = tree.find(key1)->rank;
            dtotal.slice(loc) += sn * (ddoq1.slice(m) - qddo1.slice(m));
          } else {
            keys(nddo) = hnod(nod.gams + expn(mp), key1);
            dtotal.slice(nddo) = sn * (ddoq1.slice(m) - qddo1.slice(m));
            nddo += 1;
          }
        }
      }

      for (int mp = 0; mp < nind; ++mp) { // to tier-1
        ivec key1 = gen_key(key0, mp, -1);
        if (!key1.is_empty()) {
          const int m = modLabel(mp);
          const int k = (key1.n_rows < (unsigned int)(mp + 1)) ? 1 : (key1(mp) + 1);
          const cx_double sn = -deom_ci * alpha1(m) * sqrt(k / coef_abs(mp));
          const cx_double cl = sn * coef_lft(mp);
          const cx_double cr = sn * coef_rht(mp);
          if (!tree.try_insert(key1, nddo)) {
            int loc = tree.find(key1)->rank;
            dtotal.slice(loc) += cl * ddoq1.slice(m) - cr * qddo1.slice(m);
          } else {
            keys(nddo) = hnod(nod.gams - expn(mp), key1);
            dtotal.slice(nddo) = cl * ddoq1.slice(m) - cr * qddo1.slice(m);
            nddo += 1;
          }
        }
      }
    }
  }
}
