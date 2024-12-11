import React from 'react';
import ComponentCreator from '@docusaurus/ComponentCreator';

export default [
  {
    path: '/KernelGoat/blog',
    component: ComponentCreator('/KernelGoat/blog', 'b4d'),
    exact: true
  },
  {
    path: '/KernelGoat/blog/archive',
    component: ComponentCreator('/KernelGoat/blog/archive', 'ab7'),
    exact: true
  },
  {
    path: '/KernelGoat/blog/authors',
    component: ComponentCreator('/KernelGoat/blog/authors', '9c4'),
    exact: true
  },
  {
    path: '/KernelGoat/blog/authors/all-sebastien-lorber-articles',
    component: ComponentCreator('/KernelGoat/blog/authors/all-sebastien-lorber-articles', 'baa'),
    exact: true
  },
  {
    path: '/KernelGoat/blog/authors/yangshun',
    component: ComponentCreator('/KernelGoat/blog/authors/yangshun', 'b48'),
    exact: true
  },
  {
    path: '/KernelGoat/blog/first-blog-post',
    component: ComponentCreator('/KernelGoat/blog/first-blog-post', '8ef'),
    exact: true
  },
  {
    path: '/KernelGoat/blog/long-blog-post',
    component: ComponentCreator('/KernelGoat/blog/long-blog-post', '624'),
    exact: true
  },
  {
    path: '/KernelGoat/blog/mdx-blog-post',
    component: ComponentCreator('/KernelGoat/blog/mdx-blog-post', '5de'),
    exact: true
  },
  {
    path: '/KernelGoat/blog/tags',
    component: ComponentCreator('/KernelGoat/blog/tags', 'a5b'),
    exact: true
  },
  {
    path: '/KernelGoat/blog/tags/docusaurus',
    component: ComponentCreator('/KernelGoat/blog/tags/docusaurus', '6ab'),
    exact: true
  },
  {
    path: '/KernelGoat/blog/tags/facebook',
    component: ComponentCreator('/KernelGoat/blog/tags/facebook', 'c76'),
    exact: true
  },
  {
    path: '/KernelGoat/blog/tags/hello',
    component: ComponentCreator('/KernelGoat/blog/tags/hello', 'f0f'),
    exact: true
  },
  {
    path: '/KernelGoat/blog/tags/hola',
    component: ComponentCreator('/KernelGoat/blog/tags/hola', '1ce'),
    exact: true
  },
  {
    path: '/KernelGoat/blog/welcome',
    component: ComponentCreator('/KernelGoat/blog/welcome', '9f2'),
    exact: true
  },
  {
    path: '/KernelGoat/markdown-page',
    component: ComponentCreator('/KernelGoat/markdown-page', 'afb'),
    exact: true
  },
  {
    path: '/KernelGoat/docs',
    component: ComponentCreator('/KernelGoat/docs', 'ba4'),
    routes: [
      {
        path: '/KernelGoat/docs',
        component: ComponentCreator('/KernelGoat/docs', 'ce3'),
        routes: [
          {
            path: '/KernelGoat/docs',
            component: ComponentCreator('/KernelGoat/docs', '048'),
            routes: [
              {
                path: '/KernelGoat/docs/💪 Why - The Motivation',
                component: ComponentCreator('/KernelGoat/docs/💪 Why - The Motivation', '9ef'),
                exact: true,
                sidebar: "tutorialSidebar"
              },
              {
                path: '/KernelGoat/docs/category/tutorial---basics',
                component: ComponentCreator('/KernelGoat/docs/category/tutorial---basics', 'd01'),
                exact: true,
                sidebar: "tutorialSidebar"
              },
              {
                path: '/KernelGoat/docs/category/tutorial---extras',
                component: ComponentCreator('/KernelGoat/docs/category/tutorial---extras', 'df0'),
                exact: true,
                sidebar: "tutorialSidebar"
              },
              {
                path: '/KernelGoat/docs/intro',
                component: ComponentCreator('/KernelGoat/docs/intro', 'c90'),
                exact: true,
                sidebar: "tutorialSidebar"
              },
              {
                path: '/KernelGoat/docs/tutorial-basics/congratulations',
                component: ComponentCreator('/KernelGoat/docs/tutorial-basics/congratulations', 'e31'),
                exact: true,
                sidebar: "tutorialSidebar"
              },
              {
                path: '/KernelGoat/docs/tutorial-basics/create-a-blog-post',
                component: ComponentCreator('/KernelGoat/docs/tutorial-basics/create-a-blog-post', '182'),
                exact: true,
                sidebar: "tutorialSidebar"
              },
              {
                path: '/KernelGoat/docs/tutorial-basics/create-a-document',
                component: ComponentCreator('/KernelGoat/docs/tutorial-basics/create-a-document', 'f6f'),
                exact: true,
                sidebar: "tutorialSidebar"
              },
              {
                path: '/KernelGoat/docs/tutorial-basics/create-a-page',
                component: ComponentCreator('/KernelGoat/docs/tutorial-basics/create-a-page', 'd48'),
                exact: true,
                sidebar: "tutorialSidebar"
              },
              {
                path: '/KernelGoat/docs/tutorial-basics/deploy-your-site',
                component: ComponentCreator('/KernelGoat/docs/tutorial-basics/deploy-your-site', 'eab'),
                exact: true,
                sidebar: "tutorialSidebar"
              },
              {
                path: '/KernelGoat/docs/tutorial-basics/heap_overflow',
                component: ComponentCreator('/KernelGoat/docs/tutorial-basics/heap_overflow', '179'),
                exact: true,
                sidebar: "tutorialSidebar"
              },
              {
                path: '/KernelGoat/docs/tutorial-basics/integer_overflow',
                component: ComponentCreator('/KernelGoat/docs/tutorial-basics/integer_overflow', '696'),
                exact: true,
                sidebar: "tutorialSidebar"
              },
              {
                path: '/KernelGoat/docs/tutorial-basics/markdown-features',
                component: ComponentCreator('/KernelGoat/docs/tutorial-basics/markdown-features', '2cb'),
                exact: true,
                sidebar: "tutorialSidebar"
              },
              {
                path: '/KernelGoat/docs/tutorial-basics/NullPointerDereference',
                component: ComponentCreator('/KernelGoat/docs/tutorial-basics/NullPointerDereference', '57e'),
                exact: true,
                sidebar: "tutorialSidebar"
              },
              {
                path: '/KernelGoat/docs/tutorial-basics/stack_overflow',
                component: ComponentCreator('/KernelGoat/docs/tutorial-basics/stack_overflow', '0d2'),
                exact: true,
                sidebar: "tutorialSidebar"
              },
              {
                path: '/KernelGoat/docs/tutorial-basics/Use-After-Free',
                component: ComponentCreator('/KernelGoat/docs/tutorial-basics/Use-After-Free', '014'),
                exact: true,
                sidebar: "tutorialSidebar"
              },
              {
                path: '/KernelGoat/docs/tutorial-extras/manage-docs-versions',
                component: ComponentCreator('/KernelGoat/docs/tutorial-extras/manage-docs-versions', '1e9'),
                exact: true,
                sidebar: "tutorialSidebar"
              },
              {
                path: '/KernelGoat/docs/tutorial-extras/translate-your-site',
                component: ComponentCreator('/KernelGoat/docs/tutorial-extras/translate-your-site', '875'),
                exact: true,
                sidebar: "tutorialSidebar"
              }
            ]
          }
        ]
      }
    ]
  },
  {
    path: '/KernelGoat/',
    component: ComponentCreator('/KernelGoat/', 'e97'),
    exact: true
  },
  {
    path: '*',
    component: ComponentCreator('*'),
  },
];
