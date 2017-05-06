
#include "Paragraph.h"

Paragraph::Paragraph()
{
    lines.reserve(10);
}

Paragraph::~Paragraph()
{
    for (auto&& line : lines)
    {
        delete(line);
    }

    lines.clear();
}

void Paragraph::setup(int charlength, std::string filename, std::string node)
{
    XmlFile file(filename.c_str(), "file");

    std::string data = file.getValue(node.c_str());
    std::string line = "";

    int lengthToRead = charlength;
    int previous = 0;
    int newY = y;

    bool last = false;

    while (true)
    {
        if (previous + lengthToRead >= data.size())
        {
            line = data.substr(previous);
            last = true;
        }
        else
        {
            line = data.substr(previous, lengthToRead);
        }

        int last_blank = line.find_last_of(" ");
        line = data.substr(previous, last_blank);

        Label * label = new Label();
        label->create(font, line, 60);
        label->setPosition(x, newY, align);
        lines.push_back(label);

        previous += last_blank;
        newY += 60;

        if (last)
            break;
    }
}

void Paragraph::setPosition(int x, int y, Alignment a)
{
    this->align = a;
    this->x = x;
    this->y = y;
}

void Paragraph::render(Renderer& renderer)
{
    for (int i = 0; i < lines.size(); i++)
    {
        if (lines[i] != NULL)
        {
            renderer.renderLabel(lines[i]);
        }
    }
}
