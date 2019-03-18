\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{BaseSetting}[2018/3/13 v0.1 Report Template for Report]

\LoadClass[11pt,a4paper,fancyhdr,fntef, UTF8]{ctexart}[2017/1/1]

% 调整页面大小，默认页面与常用规格不符
\RequirePackage[margin=1in,top=1.5in]{geometry}

% 插入数学公式
\RequirePackage{amsmath,amsthm,amsfonts,amssymb,bm}

% 链接点击
\RequirePackage{cite}
\RequirePackage[colorlinks,linkcolor=black,anchorcolor=blue,citecolor=green]{hyperref}

% 图表相关
\RequirePackage{float,graphicx,tikz,pgfplots,array}
% \usetikzlibrary{graphdrawing,graphs,trees,shapes,snakes,arrows,backgrounds}
% \usegdlibrary{layered}

% 用于插入C代码
\RequirePackage{minted}

% 设置页眉
\usepackage{fancyhdr}
\pagestyle{fancy}
\fancyhf{} % 清空当前的页眉页脚

%\fancyhead[L]{\heiti }
%\fancyhead[R]{\heiti }

\bibliographystyle{plain}
\numberwithin{figure}{section}

\ctexset{
    section={
        name={第,章},
        number=\arabic{section},
        format=\Large\bfseries\raggedright\heiti
    }
}

\newcommand\dlmu[2][4cm]{\hskip1pt\underline{\hb@xt@ #1{\hss#2\hss}}\hskip3pt}

%\renewcommand\maketitle{%
%    \clearpage
%    \thispagestyle{empty}
%    \begin{center}
%
%    \end{center}
%    \newpage
%}

\endinput 
 
