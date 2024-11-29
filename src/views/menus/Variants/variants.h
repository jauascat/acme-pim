#pragma once

#include "../../../views/menu.h"
#include "../../../models/variant.h"
#include "../../../models/pim.h"

namespace variants {
    class Submenu final : public Menu {
    public:
        Submenu(PIM* pim);
    };

    class GetAll final : public Operation
    {
    public:
        GetAll(PIM *pim);
        void execute() override;
    };

    class Create final : public Operation {
    public:
        Create(PIM* pim);
        void execute() override;
    };

    class Update final : public Operation {
    public:
        Update(PIM* pim);
        void execute() override;
    };

    class Delete final : public Operation {
    public:
        Delete(PIM* pim);
        void execute() override;
    };
}
