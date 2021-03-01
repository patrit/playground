FROM ubuntu:20.10

ENV TZ 'Europe/Berlin'
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get update && apt-get install -y texlive texlive-publishers texlive-latex-base texlive-latex-recommended && rm -rf /var/lib/apt/lists/* 

ENTRYPOINT ["pdflatex", "-synctex=1", "-interaction=nonstopmode", "-file-line-error", "-recorder", "-output-directory=/data"]
