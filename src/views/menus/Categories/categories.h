#pragma once

#include "../../../views/menu.h"
#include "../../../models/category.h"
#include "../../../models/pim.h"

namespace categories {
    class Submenu final : public Menu {
    public:
        Submenu(PIM* pim);
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
