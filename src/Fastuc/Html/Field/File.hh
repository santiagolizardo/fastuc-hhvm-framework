<?hh // strict
namespace Fastuc\Html\Field;

class File extends \Fastuc\Html\Field
{
	public function __construct($name) {
		$this->name = $name;
	}

	public function __toString() {
		return sprintf('<input id="%s" type="file" name="%s" />',
				$this->name, $this->name);
	}
}


