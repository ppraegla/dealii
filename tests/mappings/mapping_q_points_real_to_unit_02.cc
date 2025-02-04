// ---------------------------------------------------------------------
//
// Copyright (C) 2020 by the deal.II authors
//
// This file is part of the deal.II library.
//
// The deal.II library is free software; you can use it, redistribute
// it, and/or modify it under the terms of the GNU Lesser General
// Public License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// The full text of the license can be found in the file LICENSE.md at
// the top level directory of deal.II.
//
// ---------------------------------------------------------------------


// check MappingQ::transform_real_to_unit_points on MappingQ1 with a point
// that would at some point return an invalid answer due to a wrongly computed
// affine approximation, using a point extracted from
// tests/particles/particle_handler_21.

#include <deal.II/fe/mapping_q.h>

#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/tria.h>

#include "../tests.h"


template <int dim>
void
test()
{
  Triangulation<dim> tria;
  GridGenerator::hyper_ball(tria, Point<dim>(), 1.0);
  tria.refine_global(3);

  // pick out a particular cell
  const typename Triangulation<dim>::cell_iterator coarse_cell(&tria, 0, 5);
  const auto cell = coarse_cell->child(0)->child(5)->child(7);

  std::vector<Point<dim>> real_points{
    Point<3>(-0.0489699, -0.859053, -0.0489699)};
  std::vector<Point<dim>> unit_points(real_points.size());

  for (unsigned int degree = 1; degree < 4; ++degree)
    {
      MappingQ<dim> mapping(degree);
      mapping.transform_points_real_to_unit_cell(cell,
                                                 real_points,
                                                 unit_points);

      deallog << "Transform on cell with center: " << cell->center(true)
              << " with mapping degree " << degree << std::endl;
      deallog << "Combined transform " << real_points[0] << " gives "
              << unit_points[0] << std::endl;

      deallog << "Classic transform  " << real_points[0] << " gives "
              << mapping.transform_real_to_unit_cell(cell, real_points[0])
              << std::endl;
    }

  deallog << "OK" << std::endl;
}



int
main()
{
  initlog();
  deallog << std::setprecision(10);

  test<3>();
}
