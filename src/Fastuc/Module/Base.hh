<?hh // strict
namespace Fastuc\Module;

class Base
{
	/**
	 * @var \Fastuc\Controller\Base
	 */
	protected \Fastuc\Controller\Base $controller;

	/**
	 * @param \Fastuc\Controller\Base $controller
	 */
	public function setController( \Fastuc\Controller\Base $controller )
	{
		$this->controller = $controller;
	}

	/**
	 * @return \Fastuc\Controller\Base
	 */
	public function getController() : \Fastuc\Controller\Base
	{
		return $this->controller;
	}
}

